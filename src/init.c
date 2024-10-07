#include "init.h"
#include "paths.h"

#define SCREEN_W 640
#define SCREEN_H 480

#ifdef __EMSCRIPTEN__
#	include <emscripten.h>
#endif

void init(Context* context) {
	context->ready_to_quit = false;

	SDL_Init(SDL_INIT_EVERYTHING);

	// Init time
	// context->time_now = emscripten_get_now();
	context->time_now = SDL_GetTicks64();
	context->time_last = 0;

	// Init input
	input_map_buttons(&context->input);

	// Init DrawContext
	DrawContext* draw = &context->draw;
	draw->logical_width = LOGICAL_WIDTH;
	draw->logical_height = LOGICAL_HEIGHT;
	draw->cam_x = -((draw->logical_width - CAM_ZONE_W) / 2);
	draw->cam_y = -((draw->logical_height - CAM_ZONE_H) / 2);
	init_sprite_assets(&draw->assets);
	
	SDL_DisplayMode display_mode;
	SDL_GetDesktopDisplayMode(0, &display_mode);
	draw->screen_width = display_mode.w;
	draw->screen_height = display_mode.h;

    draw->window = SDL_CreateWindow("Stiletto", 0, 0, SCREEN_W, SCREEN_H, SDL_WINDOW_BORDERLESS);
    draw->renderer = SDL_CreateRenderer(draw->window, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderSetLogicalSize(draw->renderer, draw->logical_width, draw->logical_height);

	SDL_Surface* atlas_surface = load_surface(PATH_ATLAS);
	draw->atlas = SDL_CreateTextureFromSurface(draw->renderer, atlas_surface);

	SDL_Surface* icon_surface = load_surface(PATH_ICON);
	SDL_SetWindowIcon(draw->window, icon_surface);

	// Init AudioContext
	AudioContext* audio = &context->audio;
	audio_init(audio);

	// Init Game
	// TODO probably goes somewhere else, obviously
	#ifdef __EDITOR__
	editor_init(&context->editor);
	#else
	game_init(&context->game);
	#endif
}

SDL_Surface* load_surface(const char* path) {
    SDL_Surface* surface = SDL_LoadBMP(path);
    if(!surface) {
	    printf("Error loading surface.");
    }

    Uint32 background_color_key = SDL_MapRGB(surface->format, 255, 0, 255);
    SDL_SetColorKey(surface, 1, background_color_key);
    return surface;
}
