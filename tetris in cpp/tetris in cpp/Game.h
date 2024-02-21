#pragma once
#include "input_handler.h"
#include "Renderer.h"
#include "world_representation.h"

class game
{

public:
	world_representation world;
	game();
	void start();
	void move_flying_tetromino_if_key_pressed();

private:
	int thick_in_milliseconds_ = 200;
	renderer renderer_;
	input_handler input_handler_;
	void update();
};
