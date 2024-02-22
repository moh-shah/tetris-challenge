#pragma once
#include <queue>

enum key_code { Right, Left };

class input_handler
{

public:
	/*bool key_left_pressed_last_frame;
	bool key_right_pressed_last_frame;
	bool key_up_pressed_last_frame;
	bool key_down_pressed_last_frame;*/
	bool key_quit_pressed_last_frame;
	std::queue<key_code> key_q;

	void read_and_cache_input_key();
	void clear_buffer();
};

