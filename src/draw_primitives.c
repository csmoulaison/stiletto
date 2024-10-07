#include "draw_primitives.h"

void draw_rect(DrawContext* draw, int x, int y, int w, int h, uint32_t color) {
	uint8_t* cptr = (uint8_t*)&color;
	SDL_SetRenderDrawBlendMode(draw->renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(draw->renderer, *cptr, *(cptr+1), *(cptr+2), *(cptr+3));
	SDL_Rect rect = {x - draw->cam_x, y - draw->cam_y, w, h};
	SDL_RenderDrawRect(draw->renderer, &rect);
}

void draw_rect_absolute(DrawContext* draw, int x, int y, int w, int h, uint32_t color) {
	x += draw->cam_x;
	y += draw->cam_y;
	draw_rect(draw, x, y, w, h, color);
}
