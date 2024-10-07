#include "collision.h"

#define GRAVITY 800
#define GROUND_CHECK_DIST 0.75

void resolve_velocity_physics(Collider* subject, bool* is_grounded, float* vel_x, float* vel_y, Collider* cols, int cols_len, double dt) {
	*is_grounded = false;
	*vel_y += GRAVITY * dt;

	Collider subject_xoff = *subject;
	subject_xoff.x += *vel_x * dt;
	for(int i = 0; i < cols_len; i++) {
		if(aabb(subject_xoff, cols[i])) {
			*vel_x = 0;
		}
	}

	Collider subject_yoff = *subject;
	subject_yoff.y += *vel_y * dt;
	for(int i = 0; i < cols_len; i++) {
		if(aabb(subject_yoff, cols[i])) {
			if(*vel_y >= 0) {
				subject->y = cols[i].y - subject->h;
			}
			*vel_y = 0;
		}
	}

	Collider ground_check = *subject;
	ground_check.y += GROUND_CHECK_DIST;
	for(int i = 0; i < cols_len; i++) {
		if(aabb(ground_check, cols[i])) {
			*is_grounded = true;
		}
	}

	subject->x += *vel_x * dt;
	subject->y += *vel_y * dt;
}

bool aabb(Collider c1, Collider c2) {
	return (
		c1.x < c2.x + c2.w &&
		c1.y < c2.y + c2.h &&
		c1.y + c1.h > c2.y &&
		c1.x + c1.w > c2.x
	);
}
