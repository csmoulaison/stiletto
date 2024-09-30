#include "loop.h"
#include "context.h"
#include "sprite.h"
#include "input.h"

#ifdef __EMSCRIPTEN__
#	include <emscripten.h>
#endif

void loop(void* arg) {
	Context* context = (Context*)arg;

	// Calculate delta time
	context->time_last = context->time_now;	
	context->time_now = SDL_GetTicks64();
	double dt = (double)(context->time_now - context->time_last) / 1000;

	input_poll(&context->input);
	if(context->input.quit.held) {
		context->ready_to_quit = true;
	}

	if(context->ready_to_quit) {
		#ifdef __EMSCRIPTEN__
		emscripten_cancel_main_loop();
		#endif

		exit(0);
	}

	draw_clear(&context->draw);

	#ifdef __EDITOR__
	editor_update(&context->editor, &context->draw, &context->audio, &context->input, dt);
	#else
	game_update(&context->game, &context->draw, &context->audio, &context->input, dt);
	#endif


	draw_present(&context->draw);
}
