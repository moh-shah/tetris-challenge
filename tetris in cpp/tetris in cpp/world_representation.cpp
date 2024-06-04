#include "world_representation.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

world_representation::world_representation(const int w, const int h)
{
	width = w;
	height = h;
	grid.reserve(w);
	for (int x = 0; x < w; x++)
	{
		vector<world_cell> col;
		col.reserve(h);
		for (int i=0;i < h;i++)
		{
			col.push_back(world_cell());

		}
		
		grid.push_back(col);
	}

}

bool world_representation::is_position_valid(
	tetromino tetromino, const short diff_x, const short diff_y)
{
	for (vector<short> pos : tetromino.get_positions())
	{
		auto next_x_value = pos[0] += diff_x;
		auto next_y_value = pos[1] += diff_y;

		if (next_x_value < 0 || next_x_value >= width)
			return false;

		if (next_y_value < 0 || next_y_value >= height)
			return false;

		if (grid[next_x_value][next_y_value].filled)
			return false;
	}

	return true;
}


void world_representation::put_tetromino_on_grid(tetromino tetromino)
{
	for (vector<short> element : tetromino.get_positions())
	{
		grid[element[0]][element[1]].filled = true;
		grid[element[0]][element[1]].color = tetromino.color;
	}
}

void world_representation::clear_tetromino_from_grid(tetromino tetromino)
{
	for (vector<short> pos : tetromino.get_positions())
		grid[pos[0]][pos[1]].filled = false;
}


void world_representation::fill_cell(int x, int y)
{
	grid[x][y].filled = true;
}

void world_representation::clear_cell(int x, int y)
{
	grid[x][y].filled = false;
}

vector<short> world_representation::get_unique_and_sorted_rows_filled_by_tetromino(tetromino tetromino)
{
	auto filled_rows = vector<short>();
	for (vector<short> pos : tetromino.get_positions())
	{
		if (count(filled_rows.begin(),filled_rows.end(),pos[1]))
			continue;
		
		if (is_row_filled(pos[1]))
			filled_rows.push_back(pos[1]);
	}
	sort(filled_rows.begin(), filled_rows.end());
	return filled_rows;
}

bool world_representation::is_row_filled(const int y)
{
	for (int i = 0; i < width; ++i)
		if (grid[i][y].filled == false)
			return false;

	return true;
}

void world_representation::free_row_and_shift_upper_rows_down(const int row)
{
	for (int y = row; y > 0; --y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (y>1)
				grid[x][y].filled = grid[x][y-1].filled;
			else 
				grid[x][y].filled = false;
		}
	}
}
