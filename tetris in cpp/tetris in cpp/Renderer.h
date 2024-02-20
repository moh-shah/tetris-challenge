#pragma once
#include "world_representation.h"
class Renderer
{
public:
	void init(world_representation world);
	void draw_world(world_representation world);
	static void delay(int thick_in_milliseconds);

private:
	const int cell_size = 35;
	void fill_cell(int x,int y);
};
