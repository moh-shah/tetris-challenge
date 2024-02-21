#include "game.h"

tetromino flying_tetromino;

game::game(): world(10, 20), input_handler_()
{
	renderer_.init(world);
}

void game::start()
{
	flying_tetromino = tetromino_I();
	world.put_tetromino_on(&flying_tetromino, 2, 2);

	update();
}

void game::update()
{
	while (true)
	{
		//change it later
		world.clear_tetromino_from_grid(flying_tetromino);
		input_handler_.read_and_cache_input_key();
		move_flying_tetromino_if_key_pressed();
		world.put_tetromino_on(&flying_tetromino, 0, 0);
		renderer_.draw_world(world);
		input_handler_.clear_cached_keys();
		renderer_.delay(thick_in_milliseconds_);
	}
}

void game::move_flying_tetromino_if_key_pressed()
{
	if (input_handler_.key_down_pressed_last_frame)
	{
		if (world.can_move_tetromino(flying_tetromino, 0, 1))
			flying_tetromino.shift_positions(0, 1);
	}
	else if (input_handler_.key_up_pressed_last_frame)
	{
		if (world.can_move_tetromino(flying_tetromino, 0, -1))
			flying_tetromino.shift_positions(0, -1);
	}
	else if (input_handler_.key_right_pressed_last_frame)
	{
		if (world.can_move_tetromino(flying_tetromino, 1, 0))
			flying_tetromino.shift_positions(1, 0);
	}
	else if (input_handler_.key_left_pressed_last_frame)
	{
		if (world.can_move_tetromino(flying_tetromino, -1, 0))
			flying_tetromino.shift_positions(-1, 0);
	}
}