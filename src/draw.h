#ifndef draw_h_INCLUDED
#define draw_h_INCLUDED

#include <SDL.h>

#define LOGICAL_WIDTH 480
#define LOGICAL_HEIGHT 360

struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* atlas;

	uint8_t bg_color[3];
	int screen_width;
	int screen_height;
	int logical_width;
	int logical_height;

	float cam_x;
	float cam_y;
} typedef DrawContext;

void draw_clear(DrawContext* draw);
void draw_present(DrawContext* draw);

#endif // draw_h_INCLUDED
