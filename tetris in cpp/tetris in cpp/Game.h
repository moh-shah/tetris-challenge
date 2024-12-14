#pragma once
#include <chrono>
#include "input_handler.h"
#include "Renderer.h"
#include "world_representation.h"
#include "audio_player.h"

class game
{

public:
	world_representation world;
	game();
	void start();

private:
	renderer renderer_;
	audio_player audio_player_;
	input_handler input_handler_;
	void update();
	void process_inputs();
	void handle_gravity();
	void spawn_tetromino();
	tetromino generate_random_tetromino();
};
