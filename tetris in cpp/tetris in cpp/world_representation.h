#pragma once
#include <iostream>
#include <vector>
using namespace std;

struct world_representation
{
public:
	int width;
	int height;

	vector<vector<bool>> grid;

	world_representation(int w, int h);
	void fill_cell(int x, int y);
};