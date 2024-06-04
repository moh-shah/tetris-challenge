#pragma once
#include "world_representation.h"
class renderer
{
public:
	void init(world_representation world);
	void begin_draw();
	void end_draw();
	void show_score(int score);
	void draw_world(world_representation world);
	void get_color_of_cell(world_cell cell, Uint8& color_r, Uint8& color_g, Uint8& color_b);

private:
	const int cell_size = 35;
	const int cell_border_thickness = 2;
	const int grid_margine_x = 70;
	const int grid_margine_y = 35;
	void draw_cell(int x,int y, world_cell cell_data);
};
