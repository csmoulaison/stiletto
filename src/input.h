#ifndef input_h_INCLUDED
#define input_h_INCLUDED

#include <stdbool.h>
#include <SDL.h>

#define MAX_SCANCODE_BUTTON_MAPS 64
#define MAX_BUTTONS 32

struct {
	bool held;
	bool just_pressed;
	bool just_released;
} typedef Button;

struct {
	SDL_Scancode scancode;
	Button* button;
} typedef ScancodeButtonMap;

struct {
	ScancodeButtonMap scancode_button_maps[MAX_SCANCODE_BUTTON_MAPS];
	int scancode_button_maps_len;

	Button* mapped_buttons[MAX_BUTTONS];
	int mapped_buttons_len;

	Button quit;
	Button interact;
	Button left;
	Button right;
	Button jump;
	Button throw;
	Button bomb;

	#ifdef __EDITOR__
	Button cursor_up;
	Button cursor_left;
	Button cursor_down;
	Button cursor_right;
	Button atlas_up;
	Button atlas_left;
	Button atlas_down;
	Button atlas_right;
	Button edit_mod;
	Button edit_place;
	Button edit_place_ana;
	Button edit_serialize;
	Button edit_deserialize;
	Button edit_state_colliders;
	Button edit_collider_start;
	Button edit_collider_end;
	Button edit_collider_incr;
	Button edit_collider_deincr;
	#endif
} typedef Input;

void input_map_buttons(Input* input);
void input_poll(Input* input);
void map_scancode_to_button(Input* input, SDL_Scancode sc, Button* button);

#endif // input_h_INCLUDED
