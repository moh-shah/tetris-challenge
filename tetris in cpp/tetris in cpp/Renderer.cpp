#include "renderer.h"
#include "SDL.h"

SDL_Renderer* sdl_renderer;
int invisible_height_margin = 4;
int renderable_height;
SDL_Rect drawing_rct;

void renderer::init(world_representation world)
{
	renderable_height = world.height - invisible_height_margin;
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tetris Challenge",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		world.width * cell_size + grid_margine_x*2,
		renderable_height * cell_size + grid_margine_y*2,
		SDL_WINDOW_SHOWN
	);
	sdl_renderer = SDL_CreateRenderer(window, -1, 0);
}

void renderer::draw_world(world_representation world)
{
	SDL_RenderClear(sdl_renderer);
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);

	//fill the borders
	SDL_Rect border_rect;
	border_rect.h = renderable_height * cell_size;
	border_rect.w = world.width * cell_size;
	border_rect.x = grid_margine_x;
	border_rect.y = grid_margine_y;
	SDL_RenderDrawRect(sdl_renderer, &border_rect);

	for (int y = invisible_height_margin; y < world.height; y++)
	{
		for (int x = 0; x < world.width; x++)
		{
			draw_cell(x, y - invisible_height_margin, world.grid[x][y]);
		}
	}

	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
	SDL_RenderPresent(sdl_renderer);
}

void renderer::get_color(world_cell cell, int& color_r, int& color_g, int& color_b)
{
	color_r = 0;
	color_g = 0;
	color_b = 0;
	switch (cell.color)
	{
	case red:
		color_r = 255;
		break;

	case blue:
		color_b = 255;
		break;

	case green:
		color_g = 255;
		break;

	case yellow:
		color_r = 255;
		color_g = 255;
		break;
	}
}

void renderer::draw_cell(const int x, const int y, world_cell cell)
{
	if (cell.filled)
	{
		SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
		drawing_rct.h = cell_size;
		drawing_rct.w = cell_size;
		drawing_rct.x = grid_margine_x + x*cell_size;
		drawing_rct.y = grid_margine_y + y*cell_size;
		SDL_RenderDrawRect(sdl_renderer, &drawing_rct);

		int color_r;
		int color_g;
		int color_b;
		get_color(cell, color_r, color_g, color_b);
		SDL_SetRenderDrawColor(sdl_renderer, color_r, color_g, color_b, 255);
		drawing_rct.h -= cell_border_thickness*2;
		drawing_rct.w -= cell_border_thickness*2;
		drawing_rct.x += cell_border_thickness;
		drawing_rct.y += cell_border_thickness;
		SDL_RenderFillRect(sdl_renderer, &drawing_rct);
	}
}
