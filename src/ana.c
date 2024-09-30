#include "ana.h"

void ana_update(Ana* ana, DrawContext* draw, AudioContext* audio, Input* input, double dt) {
	ana->vel_x = 0;
	if(input->right.held) {
		ana->vel_x += ANA_SPEED_MAX;
	}
	if(input->left.held) {
		ana->vel_x -= ANA_SPEED_MAX;
	}

	if(input->jump.just_pressed && ana->is_grounded) {
		ana->vel_y -= ANA_JUMP_SPEED;
		play_sound(&audio->sound_select);
	}
}
