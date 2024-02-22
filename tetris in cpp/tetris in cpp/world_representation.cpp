#include "world_representation.h"
#include <vector>

using namespace std;

world_representation::world_representation(const int w, const int h)
{
	width = w;
	height = h;
	grid.reserve(w);
	for (int x = 0; x < w; x++)
	{
		vector<bool> col;
		col.reserve(h);
		for (int i=0;i < h;i++)
			col.push_back(false);
		
		grid.push_back(col);
	}

}

bool world_representation::can_move_tetromino(
	tetromino tetromino, short diff_x, short diff_y)
{
	for (vector<short> element : tetromino.get_positions())
	{
		auto next_x_value = element[0] += diff_x;
		auto next_y_value = element[1] += diff_y;

		if (next_x_value < 0 || next_x_value >= width)
			return false;

		if (next_y_value < 0 || next_y_value >= height)
			return false;

		if (grid[next_x_value][next_y_value])
			return false;
	}

	return true;
}


void world_representation::put_tetromino_on_grid(tetromino* tetromino)
{
	for (vector<short> element : tetromino->get_positions())
	{
		grid[element[0]][element[1]] = true;
	}
}

tetromino world_representation::put_tetromino_on(
	tetromino *tetromino, short x, short y)
{
	tetromino->shift_block_positions(x, y);
	for (vector<short> element : tetromino->get_positions())
	{
		grid[element[0]][element[1]] = true;
	}
	return *tetromino;
}

void world_representation::clear_tetromino_from_grid(
	tetromino tetromino)
{
	for (vector<short> element : tetromino.get_positions())
	{
		grid[element[0]][element[1]] = false;
	}
}


void world_representation::fill_cell(int x, int y)
{
	grid[x][y] = true;
}

void world_representation::clear_cell(int x, int y)
{
	grid[x][y] = false;
}