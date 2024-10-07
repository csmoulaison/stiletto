#ifndef ana_h_INCLUDED
#define ana_h_INCLUDED

#include <stdbool.h>
#include "draw.h"
#include "audio.h"
#include "input.h"
#include "collision.h"

#define ANA_SPEED_MAX 125
#define ANA_JUMP_SPEED 275
#define ANA_HALF_SIZE 8

struct {
	float x;
	float y;
	float vel_x;
	float vel_y;
	int direction;
	bool is_grounded;
} typedef Ana;

void ana_update(Ana* ana, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // ana_h_INCLUDED
