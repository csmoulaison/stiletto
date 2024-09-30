#ifndef context_h_INCLUDED
#define context_h_INCLUDED

#include <stdbool.h>
#include <time.h>
#include "game.h"
#include "editor.h"
#include "draw.h"
#include "audio.h"
#include "input.h"

struct {
	bool ready_to_quit;

	// For delta time calculation
	Uint64 time_last;
	Uint64 time_now;
	
	DrawContext draw;
	AudioContext audio;
	Input input;

	#ifdef __EDITOR__
	Editor editor;
	#else
	Game game;
	#endif
} typedef Context;

#endif // context_h_INCLUDED
