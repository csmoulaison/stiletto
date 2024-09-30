#ifndef ana_h_INCLUDED
#define ana_h_INCLUDED

#include <stdbool.h>
#include "draw.h"
#include "audio.h"
#include "input.h"
#include "collision.h"

#define ANA_SPEED_MAX 100
#define ANA_JUMP_SPEED 180

struct {
	float x;
	float y;
	float vel_x;
	float vel_y;
	bool is_grounded;
} typedef Ana;

void ana_update(Ana* ana, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // ana_h_INCLUDED
