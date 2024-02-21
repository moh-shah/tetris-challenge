#pragma once

class input_handler
{
public:
	bool key_left_pressed_last_frame;
	bool key_right_pressed_last_frame;
	bool key_up_pressed_last_frame;
	bool key_down_pressed_last_frame;

	void clear_cached_keys();
	void read_and_cache_input_key();
};
