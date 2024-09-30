#include "sprite.h"

void draw_sprite(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color) {
	draw_sprite_scaled(draw, sprite, pos_x, pos_y, pos_x + sprite.w, pos_y + sprite.h, color);
}

void draw_sprite_scaled(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color) {
	pos_x -= draw->cam_x;
	pos_y -= draw->cam_y;
	end_x -= draw->cam_x;
	end_y -= draw->cam_y;

    SDL_Rect src = {sprite.x, sprite.y, sprite.w, sprite.h};
    SDL_Rect dst = {pos_x, pos_y, end_x - pos_x, end_y - pos_y};
    SDL_RenderCopyEx(draw->renderer, draw->atlas, &src, &dst, 0, NULL, SDL_FLIP_NONE);
}

void draw_sprite_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color) {
	draw_sprite_scaled_absolute(draw, sprite, pos_x, pos_y, pos_x + sprite.w, pos_y + sprite.h, color);
}

void draw_sprite_scaled_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color) {
	pos_x += draw->cam_x;
	pos_y += draw->cam_y;
	end_x += draw->cam_x;
	end_y += draw->cam_y;
	draw_sprite_scaled(draw, sprite, pos_x, pos_y, end_x, end_y, color);
}
