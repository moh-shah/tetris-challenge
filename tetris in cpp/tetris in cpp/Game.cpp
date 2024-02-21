#include "Game.h"


int x = 0;
tetromino flying_tetromino;

Game::Game(): world(10,20)
{
	renderer_.init(world);
}

void Game::start()
{
	flying_tetromino = tetromino_I();
	world.put_tetromino_on(&flying_tetromino, 2, 2);

	update();
}

void Game::update()
{
	while (true)
	{
		//change it later

		if (world.can_move_tetromino(flying_tetromino,0, 1))
		{
			world.clear_tetromino_from_grid(flying_tetromino);
			flying_tetromino.shift_positions(0, 1);
			world.put_tetromino_on(&flying_tetromino, 0, 0);
		}

		renderer_.draw_world(world);
		renderer_.delay(thick_in_milliseconds_);

	}
}