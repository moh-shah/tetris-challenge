#include "game.h"
#include <thread>
#include <cstdlib>
using namespace std;
using namespace chrono;



tetromino flying_tetromino = null_tetromino(last_color);
tetromino next_tetromino = null_tetromino(last_color);

bool exit_game_loop;
bool row_cleared_in_last_update;
vector<short> cleared_rows;

//game frame-rate
time_point<steady_clock> last_frame_time;
const milliseconds desired_frame_time(33);//for 330 fps

//tetris update-state delay
time_point<steady_clock> last_state_update_time;
milliseconds game_state_update_duration(200);

game::game(): world(10, 24), input_handler_()
{
	srand(time(0));
	renderer_.init(world);
}

void game::start()
{
	update();
}

void game::update()
{
	while (!exit_game_loop)
	{
		input_handler_.read_and_cache_input_key();

		auto now = steady_clock::now();
		auto elapsed_time = duration_cast<milliseconds>(now - last_frame_time);

		//to handle game frame-rate
		if (elapsed_time >= desired_frame_time)
		{
			if (duration_cast<milliseconds>(now - last_state_update_time) >= game_state_update_duration)
			{
				if (row_cleared_in_last_update)
				{
					for (int i = cleared_rows.size() - 1; i >= 0; --i)
					{
						const auto row = cleared_rows[i];
						cout << "\n clearing row: " << row << "\n";
						world.free_row_and_shift_upper_rows_down(row);
					}
					cleared_rows.clear();
					row_cleared_in_last_update = false;
				}
				else
				{
					spawn_tetromino();

					//update game state
					world.clear_tetromino_from_grid(flying_tetromino);
					process_inputs();
					handle_gravity();
					world.put_tetromino_on_grid(flying_tetromino);

					if (flying_tetromino.is_landed)
					{
						cleared_rows = world.get_unique_and_sorted_rows_filled_by_tetromino(flying_tetromino);
						row_cleared_in_last_update = !cleared_rows.empty();
					}
				}

				renderer_.draw_world(world);
				last_state_update_time = now;
			}

			last_frame_time = now;
		}
	}
}


void game::handle_gravity()
{
	cout << "is flying tetromino landed: " << std::boolalpha << flying_tetromino.is_landed <<"\n";
	if (world.is_position_valid(flying_tetromino, 0, 1))
	{
		flying_tetromino.shift_block_positions(0, 1);
	}
	else
	{
		flying_tetromino.is_landed = true;
		input_handler_.clear_buffer();
	}
}

void game::process_inputs()
{
	if (input_handler_.key_q.empty())
		return;

	const auto peek = input_handler_.key_q.front();
	if (peek == Right)
	{
		if (world.is_position_valid(flying_tetromino, 1, 0))
			flying_tetromino.shift_block_positions(1, 0);
	}
	else if (peek == Left)
	{
		if (world.is_position_valid(flying_tetromino, -1, 0))
			flying_tetromino.shift_block_positions(-1, 0);
	}
	else if (peek == Up)
	{
		flying_tetromino.rotate(true);
		if (world.is_position_valid(flying_tetromino,0,0) == false)
			flying_tetromino.rotate(false);
	}

	input_handler_.key_q.pop();
	if (input_handler_.key_quit_pressed_last_frame)
		exit_game_loop = true;
}

tetromino game::generate_random_tetromino()
{
	tetromino tetromino1;
	const auto rnd = rand();
	cout << "random generated number: " << rnd;
	const auto random_type = static_cast<tetromino_type>(rnd % last);
	const auto random_color = static_cast<tetromino_color>(rnd % last_color);
	switch (random_type) {
		case l:
			tetromino1 = tetromino_L(random_color);
			break;
		case t:
			tetromino1 = tetromino_T(random_color);
			break;
		case s:
			tetromino1 = tetromino_S(random_color);
			break;
		case z:
			tetromino1 = tetromino_Z(random_color);
			break;
		case j:
			tetromino1 = tetromino_J(random_color);
			break;
		case o:
			tetromino1 = tetromino_O(random_color);
			break;
		case i:
		default:
			tetromino1 = tetromino_I(random_color);
		break;
	}
	return tetromino1;
}

void game::spawn_tetromino()
{
	if (flying_tetromino.type == last || flying_tetromino.is_landed)
	{
		flying_tetromino = generate_random_tetromino();
		flying_tetromino.shift_block_positions(world.width / 2, 2);
		world.put_tetromino_on_grid(flying_tetromino);
		cout << "tetromino spawned: " << flying_tetromino.type;
	}
}
