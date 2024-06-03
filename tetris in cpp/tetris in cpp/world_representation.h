#pragma once
#include <iostream>
#include <unordered_set>
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

	void shift_block_positions(const short x, const short y)
	{
		for (int i = 0; i < positions_.size(); i++)
		{
			positions_[i][0] += x;
			positions_[i][1] += y;
		}
	}

	void rotate(const bool clockwise)
	{
		//clockwise
		//new x = x*cos(90) - y*sin(90) = -y
		//new y = x*sin(90) + y*cos(90) = x

		const short direction_sign = clockwise ? 1 : -1;
		const auto init_pivot = positions_[pivot_index_];
		for (auto& position : positions_)
		{
			const auto init_x = position[0];
			const auto init_y = position[1];
			position[0] = -init_y * direction_sign;
			position[1] = init_x * direction_sign;
		}

		const auto new_pivot = positions_[pivot_index_];
		const auto diff_x = new_pivot[0] - init_pivot[0];
		const auto diff_y = new_pivot[1] - init_pivot[1];
		for (auto& position : positions_)
		{
			position[0] -= diff_x;
			position[1] -= diff_y;
		}

	}

protected:
	vector<vector<short>> positions_;
	int pivot_index_ = 0;
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
		pivot_index_ = 1;
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
		pivot_index_ = 1;
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
		pivot_index_ = 1;
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
		pivot_index_ = 2;
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
		pivot_index_ = 2;
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
		pivot_index_ = 3;
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
		pivot_index_ = 1;
	}
};



struct world_representation
{
public:
	int width;
	int height;

	vector<vector<bool>> grid;

	world_representation(int w, int h);

	bool is_position_valid(tetromino tetromino, short diff_x, short diff_y);
	void put_tetromino_on_grid(tetromino tetromino);
	void clear_tetromino_from_grid(tetromino tetromino);
	void fill_cell(int x, int y);
	void clear_cell(int x, int y);
	vector<short> get_unique_and_sorted_rows_filled_by_tetromino(tetromino tetromino);
	bool is_row_filled(int y);
	void free_row_and_shift_upper_rows_down(int y);
};