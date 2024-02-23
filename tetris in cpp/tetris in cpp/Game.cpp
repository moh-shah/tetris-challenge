#include "game.h"
#include <thread>
#include <cstdlib>
using namespace std;
using namespace chrono;



tetromino flying_tetromino = null_tetromino();
tetromino next_tetromino = null_tetromino();

bool exit_game_loop;

//game frame-rate
time_point<steady_clock> last_frame_time;
const milliseconds desired_frame_time(33);//for 330 fps

//tetris update-state delay
time_point<steady_clock> last_state_update_time;
milliseconds game_state_update_duration(1000);

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
				spawn_tetromino();

				//update game state
				world.clear_tetromino_from_grid(flying_tetromino);
				process_inputs();
				handle_gravity();
				world.put_tetromino_on_grid(&flying_tetromino);
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
	if (world.can_move_tetromino(flying_tetromino, 0, 1))
	{
		flying_tetromino.shift_block_positions(0, 1);
	}
	else
	{
		flying_tetromino.is_landed = true;
	}
}

void game::process_inputs()
{
	if (input_handler_.key_q.empty())
		return;

	const auto peek = input_handler_.key_q.front();


	if (peek == Right)
	{
		if (world.can_move_tetromino(flying_tetromino, 1, 0))
		{
			flying_tetromino.shift_block_positions(1, 0);
		}
	}
	else if (peek == Left)
	{
		if (world.can_move_tetromino(flying_tetromino, -1, 0))
		{
			flying_tetromino.shift_block_positions(-1, 0);
		}
	}
	input_handler_.key_q.pop();
	if (input_handler_.key_quit_pressed_last_frame)
	{
		exit_game_loop = true;
	}
}

tetromino game::generate_random_tetromino()
{
	tetromino tetromino1;
	auto rnd = rand();
	cout << "random generated number: " << rnd;
	auto random_type = static_cast<tetromino_type>(rnd % last);
	switch (random_type) {
		case l:
			tetromino1 = tetromino_L();
			break;
		case t:
			tetromino1 = tetromino_T();
			break;
		case s:
			tetromino1 = tetromino_S();
			break;
		case z:
			tetromino1 = tetromino_Z();
			break;
		case j:
			tetromino1 = tetromino_J();
			break;
		case o:
			tetromino1 = tetromino_O();
			break;
		case i:
			tetromino1 = tetromino_I();
			break;
		default:
			tetromino1 = tetromino_I();
		break;
	}
	return tetromino1;
}

void game::spawn_tetromino()
{
	if (flying_tetromino.type == last || flying_tetromino.is_landed)
	{
		flying_tetromino = generate_random_tetromino();
		world.put_tetromino_on(&flying_tetromino, world.width / 2, 2);
		cout << "tetromino spawned: " << flying_tetromino.type;

	}
}
