#ifndef sprite_assets_h_INCLUDED
#define sprite_assets_h_INCLUDED

#include "sprite.h"

struct {
	Sprite ana;
	Sprite stiletto;
} typedef SpriteAssets;

void init_sprite_assets(SpriteAssets* assets);

#endif // sprite_assets_h_INCLUDED
