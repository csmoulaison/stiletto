#include "editor.h"

#ifdef __EDITOR__

#define ATLAS_W 320
#define ATLAS_H 128
#define CAM_SPEED 256

void editor_init(Editor* editor) {
	editor->level.num_sprites = 0;
	
	editor->atlas_x = 0;
	editor->atlas_y = 0;
	editor->cursor_x = 0;
	editor->cursor_y = 0;
}

void editor_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	if(input->atlas_down.just_pressed) {
		editor->atlas_y += 16;
		if(editor->atlas_y >= ATLAS_H) {
			editor->atlas_y = 0;
		}
	}
	if(input->atlas_left.just_pressed) {
		editor->atlas_x -= 16;
		if(editor->atlas_x < 0) {
			editor->atlas_x = ATLAS_W - 16;
		}
	}
	if(input->atlas_up.just_pressed) {
		editor->atlas_y -= 16;
		if(editor->atlas_y < 0) {
			editor->atlas_y = ATLAS_H - 16;
		}
	}
	if(input->atlas_right.just_pressed) {
		editor->atlas_x += 16;
		if(editor->atlas_x >= ATLAS_W) {
			editor->atlas_x = 0;
		}
	}

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

	if(input->edit_place.just_pressed) {
		bool already_exists = false;
		for(int i = 0; i < editor->level.num_sprites; i++) {
			if(editor->level.sprites[i].dst_x == editor->cursor_x
			&& editor->level.sprites[i].dst_y == editor->cursor_y) {
				already_exists = true;
				editor->level.sprites[i] = editor->level.sprites[editor->level.num_sprites - 1];
				editor->level.num_sprites--;
				break;
			}
		}

		if(!already_exists) {
			editor->level.sprites[editor->level.num_sprites] = (LevelSprite){
				editor->atlas_x, 
				editor->atlas_y,
				editor->cursor_x,
				editor->cursor_y
			};
			editor->level.num_sprites++;
		}
	}

	for(int i = 0; i < editor->level.num_sprites; i++) {
		Sprite sprite = {
			editor->level.sprites[i].src_x,
			editor->level.sprites[i].src_y,
			16,
			16
		};
		draw_sprite(draw, sprite, editor->level.sprites[i].dst_x, editor->level.sprites[i].dst_y, 0);
	}
	
	Sprite atlas = {0, 0, ATLAS_W, ATLAS_H};
	draw_sprite_scaled_absolute(draw, atlas, 0, 0, ATLAS_W / 2, ATLAS_H / 2, 0);

	Sprite cursor_atlas = {288, 112, 8, 8};
	draw_sprite_absolute(draw, cursor_atlas, editor->atlas_x / 2, editor->atlas_y / 2, 0);

	Sprite cursor_sprite = {editor->atlas_x, editor->atlas_y, 16, 16};
	draw_sprite(draw, cursor_sprite, editor->cursor_x, editor->cursor_y, 0);

	Sprite cursor = {304, 112, 16, 16};
	draw_sprite(draw, cursor, editor->cursor_x, editor->cursor_y, 0);
}

#endif // ifdef editor
