#include "input_handler.h"

#include <SDL_events.h>

SDL_Event key_press_event;

void input_handler::read_and_cache_input_key()
{
	if (SDL_PollEvent(&key_press_event) && key_press_event.type == SDL_KEYDOWN)
	{
		key_left_pressed_last_frame = key_press_event.key.keysym.sym == SDLK_LEFT;
		key_right_pressed_last_frame = key_press_event.key.keysym.sym == SDLK_RIGHT;
		key_up_pressed_last_frame = key_press_event.key.keysym.sym == SDLK_UP;
		key_down_pressed_last_frame = key_press_event.key.keysym.sym == SDLK_DOWN;
	}	
}

void input_handler :: clear_cached_keys()
{
	key_down_pressed_last_frame = false;
	key_up_pressed_last_frame = false;
	key_left_pressed_last_frame = false;
	key_right_pressed_last_frame = false;
}
