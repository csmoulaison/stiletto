#include "draw.h"

void draw_clear(DrawContext* draw) {
	SDL_SetRenderDrawColor(draw->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(draw->renderer);
}

void draw_present(DrawContext* draw) {
	SDL_RenderPresent(draw->renderer);
}
