#include <stdio.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#	include <emscripten.h>
#endif

#include "loop.h"
#include "init.h"

int main() {
	Context* context = (Context*)malloc(sizeof(Context));
	init(context);

	#ifdef __EMSCRIPTEN__ 
	emscripten_set_main_loop_arg(loop, context, 0, 1);
	#else
	while(!context->ready_to_quit) {
		loop(context);
	}
	#endif

	return 0;
}
