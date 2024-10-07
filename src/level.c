#include "level.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "paths.h"
#include "sprite.h"
#include "serialize.h"

#define MAX_LEVEL_DATA_ARGS 4

void level_serialize(Level* level) {
	printf("Serializing level...\n");
	
	FILE* file = fopen(PATH_LEVEL, "w");
	if(file == NULL) {
		printf("Level data file cannot be opened for serialization!");
	}

	for(int i = 0; i < level->sprites_len; i++) {
		printf("  Serializing sprite (%i of %i)\n", i + 1, level->sprites_len);

		LevelSprite* s = &level->sprites[i];
		int32_t args[4] = {s->src_x, s->src_y, s->dst_x, s->dst_y};
		serialize_line(file, 's', args, 4);
	}

	for(int i = 0; i < level->static_colliders_len; i++) {
		printf("  Serializing static collider (%i of %i)\n", i + 1, level->static_colliders_len);

		Collider* c = &level->static_colliders[i];
		int32_t args[4] = {(int32_t)c->x, (int32_t)c->y, (int32_t)c->w, (int32_t)c->h};
		serialize_line(file, 'c', args, 4);
	}

	fclose(file);
}

void level_deserialize(Level* level) {	
	printf("Deserializing level...\n");

	FILE* file = fopen(PATH_LEVEL, "r");
	if(file == NULL) {
		printf("Level data file cannot be opened for deserialization!");
	}

	level->sprites_len = 0;
	level->static_colliders_len = 0;

	char specifier;
	int32_t args[MAX_LEVEL_DATA_ARGS];
	uint32_t args_len;

	int res = 0;
	while((res = deserialize_line(file, &specifier, args, &args_len)) != EOF) {
		switch(specifier) {
		case 's':
			level->sprites[level->sprites_len] = (LevelSprite){
				args[0],
				args[1],
				args[2],
				args[3]
			};
			level->sprites_len++;
			break;
		case 'c':
			level->static_colliders[level->static_colliders_len] = (Collider){
				args[0],
				args[1],
				args[2],
				args[3],
			};
			level->static_colliders_len++;
			break;
		default:
			break;
		}
	}
	fclose(file);
}

void draw_level_sprites(Level* level, DrawContext* draw) {
	// Draw level sprites
	for(int i = 0; i < level->sprites_len; i++) {
		Sprite sprite = {
			level->sprites[i].src_x,
			level->sprites[i].src_y,
			16,
			16
		};
		draw_sprite(draw, sprite, level->sprites[i].dst_x, level->sprites[i].dst_y, 0);
	}
}
