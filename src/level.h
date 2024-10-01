#ifndef level_h_INCLUDED
#define level_h_INCLUDED

#define MAX_LEVEL_SPRITES 2048

struct {
	uint16_t src_x;
	uint16_t src_y;
	uint16_t dst_x;
	uint16_t dst_y;
} typedef LevelSprite;

struct {
	LevelSprite sprites[MAX_LEVEL_SPRITES];
	int num_sprites;
} typedef Level;

struct {

} typedef LevelLoader;

void level_serialize(Level* level);
void level_deserialize(Level* level);

#endif // level_h_INCLUDED
