#include "Renderer.h"
#include "SDL.h"

SDL_Renderer* sdl_renderer;

void Renderer::init(world_representation world)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Tetris Challenge",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		world.width * cell_size + grid_margine_x*2,
		world.height * cell_size + grid_margine_y*2,
		SDL_WINDOW_SHOWN
	);
	sdl_renderer = SDL_CreateRenderer(window, -1, 0);
}

void Renderer::draw_world(world_representation world)
{
	SDL_RenderClear(sdl_renderer);
	SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);

	for (int y = 0; y < world.height; y++)
	{
		for (int x = 0; x < world.width; x++)
		{
			if (world.grid[x][y])
			{
				fill_cell(x, y);
			}
		}
	}

	SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
	SDL_RenderPresent(sdl_renderer);
}


void Renderer::delay(int thick_in_milliseconds)
{
	SDL_Delay(thick_in_milliseconds);
}

void Renderer::fill_cell(int x, int y)
{
	SDL_Rect rect;
	rect.h = cell_size;
	rect.w = cell_size;
	rect.x = grid_margine_x + x*cell_size;
	rect.y = grid_margine_y + y*cell_size;
	SDL_RenderDrawRect(sdl_renderer, &rect);
}
