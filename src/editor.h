#ifndef editor_h_INCLUDED
#define editor_h_INCLUDED

#include "draw.h"
#include "audio.h"
#include "input.h"
#include "sprite.h"
#include "level.h"

#ifdef __EDITOR__

struct {
	Level level;
	int atlas_x;
	int atlas_y;
	int cursor_x;
	int cursor_y;
} typedef Editor;

void editor_init(Editor* editor);
void editor_update(Editor* editor, DrawContext* draw, AudioContext* audio, Input* input, double dt);

#endif // ifdef editor

#endif // editor_h_INCLUDED
