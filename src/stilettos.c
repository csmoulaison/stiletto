#include "stilettos.h"

#include <stdio.h>
#include "collision.h"
#include "draw_sprites.h"

// Should only be called if stilettos are unlocked
void stilettos_update(Stiletto* stilettos, Ana* ana, Input* input, DrawContext* draw, AudioContext* audio, double dt) {
	if(input->throw.just_pressed) {
		for(int i = 0; i < STILETTOS_NUM; i++) {
			Stiletto* stiletto = &stilettos[i];
			if(!stiletto->available) {
				continue;
			}

			stiletto->x = ana->x + ANA_HALF_SIZE;
			stiletto->y = ana->y;
			stiletto->direction = ana->direction;
			stiletto->vel_x = STILETTO_SPEED_INIT * stiletto->direction;
			stiletto->available = false;
			break;
		}
	}
	
	for(int i = 0; i < STILETTOS_NUM; i++) {
		Stiletto* stiletto = &stilettos[i];
			if(stiletto->available) { // stiletto on foot
			continue;
		} 

		// stiletto in air
		stiletto->vel_x -= stiletto->direction * STILETTO_DECEL * dt;
		stiletto->x += stiletto->vel_x * dt;

		if((stiletto->direction == 1  && stiletto->x < ana->x - ANA_HALF_SIZE)
		|| (stiletto->direction == -1 && stiletto->x > ana->x + ANA_HALF_SIZE * 2)) {
			stiletto->available = true;
		}

	    if(ana->vel_y > 0) {
		   	Collider ana_check = {ana->x + 2, ana->y + 12, 12, 6};

		    // VOLATILE TODO should probably make some numbers less magic,
			// as it is now, these need to be calibrated alongside the sprite drawing
		    Collider stiletto_col = {stiletto->x, stiletto->y, 12, 4};

		    if(aabb(ana_check, stiletto_col)) {
				ana->vel_y -= STILETTO_BOUNCE_SPEED;
				stiletto->available = true;
		    }
	    }

	    draw_sprite(draw, draw->assets.stiletto, stiletto->x, stiletto->y, 0);
	}
}
