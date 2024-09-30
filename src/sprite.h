#ifndef sprite_h_INCLUDED
#define sprite_h_INCLUDED

#include "draw.h"

struct {
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} typedef Sprite;

void draw_sprite(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color);
void draw_sprite_scaled(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color);
void draw_sprite_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, uint32_t color);
void draw_sprite_scaled_absolute(DrawContext* draw, Sprite sprite, int pos_x, int pos_y, int end_x, int end_y, uint32_t color);

#endif // sprite_h_INCLUDED
