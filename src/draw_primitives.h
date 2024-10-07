#ifndef draw_primitives_h_INCLUDED
#define draw_primitives_h_INCLUDED

#include <stdint.h>
#include "draw.h"

void draw_rect(DrawContext* draw, int x, int y, int w, int h, uint32_t color);
void draw_rect_absolute(DrawContext* draw, int x, int y, int w, int h, uint32_t color);

#endif // draw_primitives_h_INCLUDED
