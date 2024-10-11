#ifndef game_h_INCLUDED
#define game_h_INCLUDED

#include "ana.h"
#include "draw.h"
#include "audio.h"
#include "input.h"
#include "level.h"
#include "save_data.h"
#include "stilettos.h"
#include "paths.h"

// MAX_ACTIVE_SCREENS is only used to define the other active maximums
// 9 + 3 extras for transitions
#define MAX_ACTIVE_SCREENS 12 
#define MAX_ACTIVE_TILE_SPRITES  MAX_SCREEN_SPRITES    * MAX_ACTIVE_SCREENS
#define MAX_ACTIVE_ENEMIES       MAX_SCREEN_ENEMIES  * MAX_ACTIVE_SCREENS
#define MAX_ACTIVE_TRIGGERS      MAX_SCREEN_TRIGGERS * MAX_ACTIVE_SCREENS
// There's only one checkpoint per screen
#define MAX_ACTIVE_CHECKPOINTS MAX_ACTIVE_SCREENS
// Dynamic colliders are needed, as the screen data itself only contains static
#define MAX_DYNAMIC_COLLIDERS 8
#define MAX_ACTIVE_COLLIDERS (MAX_SCREEN_COLLIDERS + MAX_DYNAMIC_COLLIDERS) * MAX_ACTIVE_SCREENS

struct {
	Level level;

	Ana ana;
	bool stilettos_unlocked;
	Stiletto stilettos[STILETTOS_NUM];

	// The data that makes up these parts of the game are loaded from screens
	// The Game struct has lists here that correspond to the lists of data
	//   found on the screens, and represents all of the active, loaded data
	// The pointer screen_current is only used to determine adjacent screens for
	//   loading. It is NOT used in the update loops of the corresponding data
	Screen* screen_current;

	Checkpoint checkpoints[MAX_ACTIVE_CHECKPOINTS];
	int checkpoints_len

	// Includes both static and dynamic colliders
	// These colliders are by themselves inert, so any dynamic colliders are
	//   responsible for managing their own data mutations
	Collider colliders[MAX_ACTIVE_COLLIDERS];
	int colliders_len;

	TileSprite tile_sprites[MAX_ACTIVE_TILE_SPRITES];
	int sprites_len;

	// Loaded from EnemyData
	Enemy enemies[MAX_ACTIVE_ENEMIES];
	int enemies_len;

	Trigger triggers[MAX_ACTIVE_TRIGGERS];
	int triggers_len;
} typedef Game;

void game_init(Game* game);
void game_update(Game* game, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // game_h_INCLUDED
