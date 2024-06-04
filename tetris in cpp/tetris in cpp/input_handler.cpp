#include "input_handler.h"
#include <iostream>
#include <SDL_events.h>

SDL_Event key_press_event;

void input_handler::clear_buffer()
{
	while (!key_q.empty()) {
		key_q.pop();
	}
}

void input_handler::read_and_cache_input_key()
{
	if (SDL_PollEvent(&key_press_event))
	{
		if (key_press_event.type == SDL_QUIT)
		{
			key_quit_pressed_last_frame = true;
		}
		if (key_press_event.type == SDL_KEYDOWN)
		{
			if (key_press_event.key.keysym.sym == SDLK_LEFT)
			{
				if (!key_q.empty() && key_q.front() == Right)
					clear_buffer();
				
				key_q.push(Left);
			}
			else if (key_press_event.key.keysym.sym == SDLK_RIGHT)
			{
				if (!key_q.empty() && key_q.front() == Left)
					clear_buffer();

				key_q.push(Right);
			}
			else if (key_press_event.key.keysym.sym == SDLK_UP)
			{
				if (!key_q.empty() && key_q.front() != Up)
					clear_buffer();

				key_q.push(Up);
			}
			
			key_quit_pressed_last_frame = key_press_event.key.keysym.sym == SDLK_ESCAPE;

			//std::cout << "key pressed: " << key_press_event.key.keysym.sym <<"\n";
		}
	}
 
}
 
