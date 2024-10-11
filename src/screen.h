#ifndef screen_h_INCLUDED
#define screen_h_INCLUDED

#include "collision.h"
#include "enemy.h"
#include "tile_sprite.h"

#define MAX_SCREEN_COLLIDERS 32
#define MAX_SCREEN_ENEMIES 8
#define MAX_SCREEN_SPRITES 128
#define MAX_SCREEN_TRIGGERS 4

struct {
	int16_t x;
	int16_t y;
	int16_t patrol_x1;
	int16_t patrol_x2;
} typedef EnemyData;

struct {
	int16_t coord_x;
	int16_t coord_y;

	int16_t checkpoint_x;
	int16_t checkpoint_y;
	bool has_checkpoint;

	Collider static_colliders[MAX_SCREEN_COLLIDERS];
	int static_colliders_len;

	EnemyData enemies[MAX_SCREEN_ENEMIES];
	int enemies_len;

	TileSprite sprites[MAX_SCREEN_SPRITES];
	int sprites_len;

	Trigger triggers[MAX_SCREEN_TRIGGERS];
	int triggers_len;
} typedef Screen;

#endif // screen_h_INCLUDED
