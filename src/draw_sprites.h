#ifndef draw_sprites_h_INCLUDED
#define draw_sprites_h_INCLUDED

#include <stdbool.h>
#include "draw.h"

void draw_sprite(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color);
void draw_sprite_flip(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, bool flipped, uint32_t color);
void draw_sprite_scaled(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color);
void draw_sprite_scaled_flip(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, bool flipped, uint32_t color);
void draw_sprite_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color);
void draw_sprite_scaled_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color);

#endif // draw_sprites_h_INCLUDED
