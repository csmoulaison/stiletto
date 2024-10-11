#ifndef editor_h_INCLUDED
#define editor_h_INCLUDED

#ifdef __EDITOR__

#include "draw.h"
#include "draw_primitives.h"
#include "audio.h"
#include "input.h"
#include "draw_sprites.h"
#include "level.h"
#include "save_data.h"
#include "paths.h"

enum EditorState {
	NORMAL,
	COLLIDERS
};

struct {
	Level level;
	char level_path[MAX_LEVEL_PATH_LEN];
	SaveData save;
	
	enum EditorState state;
	int cursor_x;
	int cursor_y;

	int atlas_x;
	int atlas_y;

	uint32_t collider_index;
} typedef Editor;

void editor_init(Editor* editor);
void editor_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt);
void editor_sprites_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt);
void editor_collision_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // ifdef editor

#endif // editor_h_INCLUDED
