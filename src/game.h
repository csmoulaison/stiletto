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

struct {
	Level level;

	Ana ana;
	bool stilettos_unlocked;
	Stiletto stilettos[STILETTOS_NUM];
} typedef Game;

void game_init(Game* game);
void game_update(Game* game, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // game_h_INCLUDED
