#include "sprite.h"

Sprite sprite_flipped(Sprite sprite) {
	return (Sprite){sprite.x + sprite.w, sprite.y + sprite.h, -sprite.w, -sprite.h};
}
