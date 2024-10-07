#include "game.h"
#include "sprite.h"

#ifndef __EDITOR__

void game_init(Game* game) {
	SaveData save;
	save_data_deserialize(&save, PATH_SAVE_INIT);
	
	game->ana.x = save.ana_x;
	game->ana.y = save.ana_y;

	game->ana.vel_x = 0;
	game->ana.vel_y = 0;
	game->ana.is_grounded = false;
	game->ana.direction = 1;

	game->stilettos_unlocked = true;
	game->stilettos[0].available = true;
	game->stilettos[1].available = true;

	level_deserialize(&game->level);
}

void game_update(Game* game, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	draw_level_sprites(&game->level, draw);

	ana_update(&game->ana, draw, audio, input, dt);
	stilettos_update(game->stilettos, &game->ana, input, draw, audio, dt);

	Collider col_ana = (Collider){game->ana.x, game->ana.y, 16, 16};
	resolve_velocity_physics(&col_ana, &game->ana.is_grounded, &game->ana.vel_x, &game->ana.vel_y, game->level.static_colliders, game->level.static_colliders_len, dt); 
	game->ana.x = col_ana.x;
	game->ana.y = col_ana.y;

	// TODO move this
	Sprite sprite;
	sprite.x = 0;
	sprite.y = 0;
	sprite.w = 16;
	sprite.h = 16;
	draw_sprite_flip(draw, sprite, game->ana.x, game->ana.y, (game->ana.direction != 1), 0);
}

#endif // ifndef editor
