#ifndef stilettos_h_INCLUDED
#define stilettos_h_INCLUDED

#include "ana.h"
#include "draw.h"
#include "audio.h"

#define STILETTO_SPEED_INIT 300
#define STILETTO_DECEL 400
#define STILETTOS_NUM 2
#define STILETTO_BOUNCE_SPEED 600

struct {
	float x;
	float y;
	float vel_x;
	int direction;
	bool available;
} typedef Stiletto;

void stilettos_update(Stiletto* stilettos, Ana* ana, Input* input, DrawContext* draw, AudioContext* audio, double dt);

#endif // stilettos_h_INCLUDED
