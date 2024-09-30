#ifndef collision_h_INCLUDED
#define collision_h_INCLUDED

#include <stdbool.h>

#define MAX_STATIC_COLLIDERS 128

struct {
	float x;
	float y;
	float w;
	float h;
} typedef Collider;

void resolve_velocity_physics(Collider* subject, bool* is_grounded, float* vel_x, float* vel_y, Collider* cols, int cols_len, double dt);
bool aabb(Collider c1, Collider c2);

#endif // collision_h_INCLUDED
