/*
The data format for levels deserves explanation here.
The data is stored in plain text format as a series of lines.
The first character of a line is a letter, specifying the type of data
After the line type specifier, an arbitrary amount of numbers follow.
The meaning of these numbers depends on the type of data.
For instance: Sprites are   src_x, src_y, dst_x, dst_y
			  Colliders are x, y, w, h

So for example:
s0 16 64 96 
c32 32 128 16 

Yhe final line must have a newline at the end.

Formally:
<specifier><num1><space><num2><space>...<numx><newline>
<specifier><num1><space><num2><space>...<numx><newline>
<EOF>
*/

#ifndef level_h_INCLUDED
#define level_h_INCLUDED

#include <stdint.h>
#include "collision.h"
#include "draw_sprites.h"

#define CAM_ZONE_OFF_X       0
#define CAM_ZONE_OFF_Y       0
#define CAM_ZONE_W 288
#define CAM_ZONE_H 208
#define MAX_LEVEL_SPRITES    1024
#define MAX_STATIC_COLLIDERS 128

struct {
	int src_x;
	int src_y;
	int dst_x;
	int dst_y;
} typedef LevelSprite;

struct {
	LevelSprite sprites[MAX_LEVEL_SPRITES];
	int sprites_len;

	Collider static_colliders[MAX_STATIC_COLLIDERS];
	int static_colliders_len;
} typedef Level;

void level_serialize(Level* level);
void level_deserialize(Level* level);
void draw_level_sprites(Level* level, DrawContext* draw);

#endif // level_h_INCLUDED
