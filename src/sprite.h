#ifndef sprite_h_INCLUDED
#define sprite_h_INCLUDED

#include <stdint.h>

struct {
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
} typedef Sprite;

Sprite sprite_flipped(Sprite sprite);

#endif // sprite_h_INCLUDED
