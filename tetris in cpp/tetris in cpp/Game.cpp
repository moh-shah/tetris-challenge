#include "Game.h"


Game::Game(): world(10,20)
{
	renderer_.init(world);
}

void Game::update()
{
	while (true)
	{
		//change it later
	
		renderer_.draw_world(world);
		renderer_.delay(thick_in_milliseconds_);
	}
}

void Game::start()
{
	world.fill_cell(4, 7);
	world.fill_cell(4, 6);
	world.fill_cell(3, 6);
	world.fill_cell(4, 5);
	update();
}

