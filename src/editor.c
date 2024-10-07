#include "editor.h"

#ifdef __EDITOR__

#define ATLAS_W 320
#define ATLAS_H 128
#define CAM_SPEED 512
// Gizmo colors
#define COLOR_COLLISION_SELECTED 0xFF4444FF
#define COLOR_COLLISION_UNSELECTED 0x883333FF
#define COLOR_CAM_ZONE 0x4444DDFF
#define COLOR_CAM_ZONE_BUFFER 0x4444DD88

void editor_init(Editor* editor) {
	editor->level.sprites_len = 0;
	editor->level.static_colliders_len = 0;

	editor->state =	NORMAL;
	editor->cursor_x = 0;
	editor->cursor_y = 0;

	editor->atlas_x = 0;
	editor->atlas_y = 0;

	editor->collider_index = 0;
}

void editor_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	// Save/load
	if(input->edit_serialize.just_pressed) {
		level_serialize(&editor->level);
		save_data_serialize(&editor->save, PATH_SAVE_INIT);
	}

	if(input->edit_deserialize.just_pressed) {
		level_deserialize(&editor->level);
		save_data_deserialize(&editor->save, PATH_SAVE_INIT);
	}

	// Control state
	if(input->edit_state_colliders.just_pressed) {
		if(editor->state != COLLIDERS) {
			editor->state = COLLIDERS;
		} else {
			editor->state = NORMAL;
		}
	}

	// Control main cursor
	if(input->edit_mod.held) {
		if(input->cursor_up.held) draw->cam_y -= CAM_SPEED * dt;
		if(input->cursor_left.held) draw->cam_x -= CAM_SPEED * dt;
		if(input->cursor_down.held) draw->cam_y += CAM_SPEED * dt;
		if(input->cursor_right.held) draw->cam_x += CAM_SPEED * dt;
	} else {
		if(input->cursor_up.just_pressed) editor->cursor_y -= 16;
		if(input->cursor_left.just_pressed) editor->cursor_x -= 16;
		if(input->cursor_down.just_pressed) editor->cursor_y += 16;
		if(input->cursor_right.just_pressed) editor->cursor_x += 16;
	}

	// Place specific objects
	if(input->edit_place_ana.just_pressed) {
		editor->save.ana_x = editor->cursor_x;
		editor->save.ana_y = editor->cursor_y;
	}

	// Draw cam zones
	int left = (int)draw->cam_x - ((int)draw->cam_x % CAM_ZONE_W);
	int top  = (int)draw->cam_y - ((int)draw->cam_y % CAM_ZONE_H);
	draw_rect(draw, left, top, CAM_ZONE_W, CAM_ZONE_H, COLOR_CAM_ZONE);
	draw_rect(draw, left - CAM_ZONE_W, top, CAM_ZONE_W, CAM_ZONE_H, COLOR_CAM_ZONE);
	draw_rect(draw, left + CAM_ZONE_W, top, CAM_ZONE_W, CAM_ZONE_H, COLOR_CAM_ZONE);
	draw_rect(draw, left, top - CAM_ZONE_H, CAM_ZONE_W, CAM_ZONE_H, COLOR_CAM_ZONE);
	draw_rect(draw, left, top + CAM_ZONE_H, CAM_ZONE_W, CAM_ZONE_H, COLOR_CAM_ZONE);
	draw_rect(draw, 
		left - (draw->logical_width  - CAM_ZONE_W) / 2,
		top  - (draw->logical_height - CAM_ZONE_H) / 2,
		draw->logical_width,
		draw->logical_height,
		COLOR_CAM_ZONE_BUFFER
	);
	draw_rect(draw, 
		left + (draw->logical_width  - CAM_ZONE_W) / 2,
		top  + (draw->logical_height - CAM_ZONE_H) / 2,
		CAM_ZONE_W * 2 - draw->logical_width,
		CAM_ZONE_H * 2 - draw->logical_height,
		COLOR_CAM_ZONE_BUFFER
	);

	// Draw level sprites
	draw_level_sprites(&editor->level, draw);

	// Draw ana
	draw_sprite(draw, draw->assets.ana, editor->save.ana_x, editor->save.ana_y, 0);

	switch(editor->state) {
	case NORMAL:
		editor_sprites_update(editor, draw, audio, input, dt);
		break;
	case COLLIDERS:
		editor_collision_update(editor, draw, audio, input, dt);
		break;
	default:
		break;
	}

	// Draw main cursor
	Sprite cursor = {304, 112, 16, 16};
	draw_sprite(draw, cursor, editor->cursor_x, editor->cursor_y, 0);
}

void editor_sprites_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	// Control sprite atlas cursor
	if(input->atlas_down.just_pressed) {
		editor->atlas_y += 16;
		if(editor->atlas_y >= ATLAS_H) editor->atlas_y = 0;
	}
	if(input->atlas_left.just_pressed) {
		editor->atlas_x -= 16;
		if(editor->atlas_x < 0)	editor->atlas_x = ATLAS_W - 16;
	}
	if(input->atlas_up.just_pressed) {
		editor->atlas_y -= 16;
		if(editor->atlas_y < 0)	editor->atlas_y = ATLAS_H - 16;
	}
	if(input->atlas_right.just_pressed) {
		editor->atlas_x += 16;
		if(editor->atlas_x >= ATLAS_W) editor->atlas_x = 0;
	}

	// Place sprites
	if(input->edit_place.just_pressed) {
		bool already_exists = false;
		for(int i = 0; i < editor->level.sprites_len; i++) {
			if(editor->level.sprites[i].dst_x == editor->cursor_x
			&& editor->level.sprites[i].dst_y == editor->cursor_y) {
				already_exists = true;
				editor->level.sprites[i] = editor->level.sprites[editor->level.sprites_len - 1];
				editor->level.sprites_len--;
				break;
			}
		}

		if(!already_exists) {
			editor->level.sprites[editor->level.sprites_len] = (LevelSprite){
				editor->atlas_x, 
				editor->atlas_y,
				editor->cursor_x,
				editor->cursor_y
			};
			editor->level.sprites_len++;
		}
	}

	// Draw the sprite atlas, atlas cursor, and sprite under main cursor
	Sprite atlas = {0, 0, ATLAS_W, ATLAS_H};
	draw_sprite_scaled_absolute(draw, atlas, 0, 0, ATLAS_W / 2, ATLAS_H / 2, 0);

	Sprite cursor_atlas = {288, 112, 8, 8};
	draw_sprite_absolute(draw, cursor_atlas, editor->atlas_x / 2, editor->atlas_y / 2, 0);

	// VOLATILE in order to draw the cursor under the sprite, editor_sprites_update
	// needs to be called before the main cursor sprite is drawn
	Sprite cursor_sprite = {editor->atlas_x, editor->atlas_y, 16, 16};
	draw_sprite(draw, cursor_sprite, editor->cursor_x, editor->cursor_y, 0);
}

void editor_collision_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	bool collider_selected = false;
	if(input->edit_collider_incr.just_pressed && editor->collider_index < editor->level.static_colliders_len) {
		editor->collider_index++;
		collider_selected = true;
	}

	if(input->edit_collider_deincr.just_pressed && editor->collider_index > 0) {
		editor->collider_index--;
		collider_selected = true;
	}

	if(collider_selected) {
		printf("Collider %u of %u selected.\n", editor->collider_index + 1, editor->level.static_colliders_len);
		if(editor->collider_index == editor->level.static_colliders_len) {
			printf("  (inactive collider)\n");
		}
	}
	
	// collider_index MUST NOT be allowed to iterate past the first non active collider
	Collider* col = &editor->level.static_colliders[editor->collider_index];
	
	if(input->edit_place.just_pressed) {	
		printf("Placing static collider at [%i, %i].\n", editor->cursor_x, editor->cursor_y);
		if(editor->collider_index == editor->level.static_colliders_len) {
			editor->level.static_colliders_len++;
			printf("Iterating static colliders (%i).\n", editor->level.static_colliders_len);
		}

		col->x = editor->cursor_x;
		col->y = editor->cursor_y;
		col->w = 16;
		col->h = 16;
	}

	if(input->atlas_up.just_pressed) {
		if(col->h > 16) col->h -= 16;
	}

	if(input->atlas_left.just_pressed) {
		if(col->w > 16) col->w -= 16;
	}

	if(input->atlas_down.just_pressed) {
		col->h += 16;
	}

	if(input->atlas_right.just_pressed) {
		col->w += 16;
	}

	for(int i = 0; i < editor->level.static_colliders_len; i++) {
		Collider* cur = &editor->level.static_colliders[i];

		uint32_t color = COLOR_COLLISION_UNSELECTED;
		if(i == editor->collider_index) {
			color = COLOR_COLLISION_SELECTED;
		}

		draw_rect(draw, cur->x, cur->y, cur->w, cur->h, color);
	}
}

#endif // ifdef editor
