#ifndef animation_h_INCLUDED
#define animation_h_INCLUDED

#define ANIM_MAX_FRAMES 8

struct {
	int x;
	int y;
	float length;
} AnimationFrame;

struct {
	AnimationFrame frames[ANIM_MAX_FRAMES];
	int frames_len;
	float speed;
} typedef Animation;

#endif // animation_h_INCLUDED
