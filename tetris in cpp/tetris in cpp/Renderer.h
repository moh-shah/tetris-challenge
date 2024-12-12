#pragma once
#include "world_representation.h"
class renderer
{
public:
	void init(world_representation world);
	void begin_draw();
	void end_draw();
	void show_side_rect_stuff(int score, tetromino next_tetromino);
	void draw_world(world_representation world);
	void show_game_result(int score);
	void get_color_of_cell(tetromino_color col, Uint8& color_r, Uint8& color_g, Uint8& color_b);

private:
	const int normal_cell_size = 35;
	const int small_cell_size = normal_cell_size/2;
	const int side_rect_width = 140;
	const int side_rect_height = 200;
	const int cell_border_thickness = 2;
	const int grid_margin_x = 150;
	const int grid_margin_y = 35;
	void draw_cell(int x,int y, world_cell cell_data);
	void draw_block(int x, int y, tetromino_color color, int cell_size);
};
