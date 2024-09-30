#include "input.h"

void input_poll(Input* input) {
	for(int i = 0; i < input->mapped_buttons_len; i++) {
		input->mapped_buttons[i]->just_pressed  = false;
		input->mapped_buttons[i]->just_released = false;
	}
	
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
        case SDL_QUIT:
            input->quit.held = true;
            break;
        case SDL_KEYDOWN:
	        for(int i = 0; i < input->scancode_button_maps_len; i++) {
		        ScancodeButtonMap* map = &input->scancode_button_maps[i];
                if(e.key.keysym.scancode == map->scancode && !map->button->held) {
                    map->button->held = true;
                    map->button->just_pressed = true;
                }
            }
            break;
        case SDL_KEYUP:
	        for(int i = 0; i < input->scancode_button_maps_len; i++) {
		        ScancodeButtonMap* map = &input->scancode_button_maps[i];
                if(e.key.keysym.scancode == map->scancode) {
                    if(map->button->held) {
                        map->button->just_released = true;
                    }
                    map->button->held = false;
                }
            }
            break;
        default:
            break;
        }
    }
}

void input_map_buttons(Input* input) {
	map_scancode_to_button(input, SDL_SCANCODE_ESCAPE, &input->quit);
	map_scancode_to_button(input, SDL_SCANCODE_F, &input->interact);
	map_scancode_to_button(input, SDL_SCANCODE_A, &input->left);
	map_scancode_to_button(input, SDL_SCANCODE_D, &input->right);
	map_scancode_to_button(input, SDL_SCANCODE_SPACE, &input->jump);
	map_scancode_to_button(input, SDL_SCANCODE_E, &input->throw);
	map_scancode_to_button(input, SDL_SCANCODE_Q, &input->bomb);

	#ifdef __EDITOR__
	map_scancode_to_button(input, SDL_SCANCODE_UP, &input->cursor_up);
	map_scancode_to_button(input, SDL_SCANCODE_LEFT, &input->cursor_left);
	map_scancode_to_button(input, SDL_SCANCODE_DOWN, &input->cursor_down);
	map_scancode_to_button(input, SDL_SCANCODE_RIGHT, &input->cursor_right);
	map_scancode_to_button(input, SDL_SCANCODE_W, &input->atlas_up);
	map_scancode_to_button(input, SDL_SCANCODE_A, &input->atlas_left);
	map_scancode_to_button(input, SDL_SCANCODE_S, &input->atlas_down);
	map_scancode_to_button(input, SDL_SCANCODE_D, &input->atlas_right);
	map_scancode_to_button(input, SDL_SCANCODE_LSHIFT, &input->edit_mod);
	map_scancode_to_button(input, SDL_SCANCODE_RETURN, &input->edit_place);
	#endif
}

void map_scancode_to_button(Input* input, SDL_Scancode sc, Button* button) {
    input->scancode_button_maps[input->scancode_button_maps_len] = (ScancodeButtonMap){sc, button};
    input->scancode_button_maps_len++;

    bool matched_button = false;
	for(int i = 0; i < input->mapped_buttons_len; i++) {
        if(input->mapped_buttons[i] == button) {
            matched_button = true;
        }
    }

    if(!matched_button) {
        input->mapped_buttons[input->mapped_buttons_len] = button;
        input->mapped_buttons_len++;
    }
}
