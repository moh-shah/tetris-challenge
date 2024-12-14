#pragma once

#include <iostream>
#include <SDL_stdinc.h>
#include <unordered_set>
#include <vector>

using namespace std;


enum tetromino_type {
    l, t, s, z, j, o, i, last
};

enum tetromino_color {
    green, blue, red, yellow, last_color
};

struct tetromino {
public:
    tetromino_type type;
    bool is_landed = false;
    tetromino_color color;

    tetromino() {}

    tetromino(tetromino_color initColor) {
        color = initColor;
    }

    vector<vector<short>> get_positions() {
        return positions_;
    }

    void shift_block_positions(const short x, const short y) {
        for (int i = 0; i < positions_.size(); i++) {
            positions_[i][0] += x;
            positions_[i][1] += y;
        }
    }

    virtual void rotate(const bool clockwise) {
        //clockwise
        //new x = x*cos(90) - y*sin(90) = -y
        //new y = x*sin(90) + y*cos(90) = x

        const short direction_sign = clockwise ? 1 : -1;
        const auto init_pivot = positions_[pivot_index_];
        for (auto &position: positions_) {
            const auto init_x = position[0];
            const auto init_y = position[1];
            position[0] = -init_y * direction_sign;
            position[1] = init_x * direction_sign;
        }

        const auto new_pivot = positions_[pivot_index_];
        const auto diff_x = new_pivot[0] - init_pivot[0];
        const auto diff_y = new_pivot[1] - init_pivot[1];
        for (auto &position: positions_) {
            position[0] -= diff_x;
            position[1] -= diff_y;
        }

    }

protected:
    vector<vector<short>> positions_;
    int pivot_index_ = 0;
};

struct null_tetromino : tetromino {
public:
    null_tetromino(const tetromino_color init_color) : tetromino(init_color) {
        type = tetromino_type::last;
    }
};

struct tetromino_L : tetromino {
public:
    tetromino_L(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 0},
                vector<short>{0, 0},
                vector<short>{1, 0},
                vector<short>{1, 1}
        };
        type = l;
        pivot_index_ = 1;
    }

};

struct tetromino_T : tetromino {
public:
    tetromino_T(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 0},
                vector<short>{0, 0},
                vector<short>{1, 0},
                vector<short>{0, 1}
        };
        type = t;
        pivot_index_ = 1;
    }
};

struct tetromino_S : tetromino {
public:
    tetromino_S(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 0},
                vector<short>{0, 0},
                vector<short>{0, 1},
                vector<short>{1, 1}
        };
        type = s;
        pivot_index_ = 1;
    }
};

struct tetromino_Z : tetromino {
public:
    tetromino_Z(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 1},
                vector<short>{0, 1},
                vector<short>{0, 0},
                vector<short>{1, 0}
        };
        type = z;
        pivot_index_ = 2;
    }
};


struct tetromino_J : tetromino {
public:
    tetromino_J(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 1},
                vector<short>{-1, 0},
                vector<short>{0, 0},
                vector<short>{1, 0}
        };
        type = j;
        pivot_index_ = 2;
    }
};

struct tetromino_O : tetromino {
public:
    tetromino_O(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{0, 1},
                vector<short>{1, 1},
                vector<short>{1, 0},
                vector<short>{0, 0}
        };
        type = o;
        pivot_index_ = 3;
    }

    void rotate(const bool clockwise) override{
        std::cout<<"not rotating :D"<<endl;//not working
    }
};

struct tetromino_I : tetromino {
public:
    tetromino_I(const tetromino_color init_color) : tetromino(init_color) {
        positions_ = {
                vector<short>{-1, 0},
                vector<short>{0, 0},
                vector<short>{1, 0},
                vector<short>{2, 0}
        };
        type = i;
        pivot_index_ = 1;
    }
};


struct world_cell {
public:
    bool filled;
    tetromino_color color;

    world_cell() {
        filled = false;
    }
};

struct world_representation {
public:
    int width;
    int height;

    vector<vector<world_cell>> grid;

    world_representation(int w, int h);

    bool can_move_to(tetromino tetromino, short diff_x, short diff_y);

    void put_tetromino_on_grid(tetromino tetromino);

    void clear_tetromino_from_grid(tetromino tetromino);

    vector<short> get_unique_and_sorted_rows_filled_by_tetromino(tetromino tetromino);

    bool is_row_filled(int y);

    void free_row_and_shift_upper_rows_down(int row);
};


