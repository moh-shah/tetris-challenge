#include "world_representation.h"

#include <vector>

using namespace std;

world_representation::world_representation(int w, int h)
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

void world_representation::fill_cell(int x, int y)
{
	grid[x][y] = true;
}