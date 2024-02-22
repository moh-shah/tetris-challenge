#pragma once
#include <iostream>
#include <vector>
 
using namespace std;




struct tetromino
{
public:

	vector<vector<short>> get_positions()
	{
		return positions_;
	}

	void shift_block_positions(short x, short y)
	{
		for (int i = 0; i < positions_.size(); i++)
		{
			positions_[i][0] += x;
			positions_[i][1] += y;
		}
	}

protected:
	vector<vector<short>> positions_;
};

struct tetromino_L : tetromino
{
public:
	/*~tetromino_L() override
	{
		delete &positions_;
	}*/
	tetromino_L()
	{
		positions_= {
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{1,0},
		vector<short>{1,1}
		};
	}
	
};

struct tetromino_T : tetromino
{
public:
	tetromino_T()
	{
		positions_ = {
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{1,0},
		vector<short>{0,1}
		};
	}
};

struct tetromino_S : tetromino
{
public:
	tetromino_S()
	{
		positions_ = {
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{0,1},
		vector<short>{1,1}
		};
	}
};

struct tetromino_Z : tetromino
{
public:
	tetromino_Z()
	{
		positions_ = {
		vector<short>{-1,1},
		vector<short>{0,1},
		vector<short>{0,0},
		vector<short>{0,1}
		};
	}
};


struct tetromino_J : tetromino
{
public:
	tetromino_J()
	{
		positions_ = {
		vector<short>{-1,1},
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{1,0}
		};
	}
};

struct tetromino_O : tetromino
{
public:
	tetromino_O()
	{
		positions_ = {
		vector<short>{0,1},
		vector<short>{1,1},
		vector<short>{1,0},
		vector<short>{0,0}
		};
	}
};

struct tetromino_I : tetromino
{
public:
	tetromino_I()
	{
		positions_ = {
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{1,0},
		vector<short>{2,0}
		};
	}
};



struct world_representation
{
public:
	int width;
	int height;

	vector<vector<bool>> grid;

	world_representation(int w, int h);

	bool can_move_tetromino(tetromino tetromino, short diff_x, short diff_y);
	tetromino put_tetromino_on(tetromino *tetromino, short x, short y);
	void put_tetromino_on_grid(tetromino *tetromino);
	void clear_tetromino_from_grid(tetromino tetromino);
	void fill_cell(int x, int y);
	void clear_cell(int x, int y);
};