#pragma once
#include "Renderer.h"
#include "world_representation.h"

class Game
{

public:
	world_representation world;
	Game();
	void start();
 

private:
	int thick_in_milliseconds_ = 15;
	Renderer renderer_;
	void update();
};
