#pragma once
#include <chrono>
#include "input_handler.h"
#include "Renderer.h"
#include "world_representation.h"

class game
{

public:
	world_representation world;
	game();
	void start();

private:
	int thick_in_milliseconds_ = 1000;
	renderer renderer_;
	input_handler input_handler_;
	void update();
	void process_inputs();
	void handle_gravity();
};
