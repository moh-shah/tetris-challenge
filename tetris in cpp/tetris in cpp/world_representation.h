#pragma once
#include <iostream>
#include <vector>

using namespace std;


enum tetromino_type
{
	l,t,s,z,j,o,i,last
};

struct tetromino
{
public:
	tetromino_type type;
	bool is_landed=false;
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

struct null_tetromino : tetromino
{
public:
	null_tetromino()
	{
		type = last;
	}
};

struct tetromino_L : tetromino
{
public:
	tetromino_L()
	{
		positions_= {
		vector<short>{-1,0},
		vector<short>{0,0},
		vector<short>{1,0},
		vector<short>{1,1}
		};
		type = l;
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
		type = t;
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
		type = s;
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
		vector<short>{1,0}
		};
		type = z;
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
		type = j;
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
		type = o;
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
		type = i;
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