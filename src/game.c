#include "game.h"
#include "sprite.h"

#ifndef __EDITOR__

void game_init(Game* game) {
	game->ana.x = 32;
	game->ana.y = 0;
	game->ana.vel_x = 0;
	game->ana.vel_y = 0;
	game->ana.is_grounded = false;

	game->static_colliders_len = 0;

	game->static_colliders[0] = (Collider){0, 200, 200, 16};
	game->static_colliders_len++;
}

void game_update(Game* game, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	ana_update(&game->ana, draw, audio, input, dt);

	Collider col_ana = (Collider){game->ana.x, game->ana.y, 16, 16};
	resolve_velocity_physics(&col_ana, &game->ana.is_grounded, &game->ana.vel_x, &game->ana.vel_y, game->static_colliders, game->static_colliders_len, dt); 
	game->ana.x = col_ana.x;
	game->ana.y = col_ana.y;

	if(input->interact.just_pressed) {
		game->ana.x += 1;
		play_sound(&audio->sound_select);
	}

	{
		Sprite sprite;
		sprite.x = 0;
		sprite.y = 0;
		sprite.w = 16;
		sprite.h = 16;
		draw_sprite(draw, sprite, game->ana.x, game->ana.y, 0);
	}

	Sprite sprite;
	sprite.x = 16;
	sprite.y = 32;
	sprite.w = 16;
	sprite.h = 16;
	Collider* col = &game->static_colliders[0];
	draw_sprite_scaled(draw, sprite, col->x, col->y, col->x + col->w, col->y + col->h, 0);
}

#endif // ifndef editor
