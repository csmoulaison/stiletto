#ifndef game_h_INCLUDED
#define game_h_INCLUDED

#ifndef __EDITOR__

#include "ana.h"
#include "draw.h"
#include "audio.h"
#include "input.h"

struct {
	Ana ana;
	Collider static_colliders[MAX_STATIC_COLLIDERS];
	int static_colliders_len;
} typedef Game;

void game_init(Game* game);
void game_update(Game* game, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // ifndef editor

#endif // game_h_INCLUDED
