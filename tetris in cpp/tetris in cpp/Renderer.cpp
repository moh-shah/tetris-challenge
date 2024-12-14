#include "renderer.h"
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"


SDL_Renderer *sdl_renderer;
SDL_Rect drawing_rct;
SDL_Color color_white = {0xff, 0xff, 0xff};
SDL_Color color_empty = {0xff, 0xff, 0xff, 0x00};
SDL_Color color_black = {0x00, 0x00, 0x00};
SDL_Window *window;
int invisible_height_margin = 4;
int renderable_height;


void draw_text_to_renderer(const string& text, int size, int x, int y, SDL_Color color) {
    // Create the text surface using the existing drawText logic
    TTF_Font *font = TTF_OpenFont(R"(.\Assets\Fonts\VT323-Regular.ttf)", size);
    if (!font) {
        printf("[ERROR] TTF_OpenFont() Failed with: %s\n", TTF_GetError());
        exit(2);
    }
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    //SDL_Surface *textSurface = TTF_RenderText_Shaded(font, text, color, bgC);
    auto char_array = text.c_str();
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, char_array, color);
    if (!textSurface) {
        TTF_CloseFont(font);
        printf("[ERROR] TTF_RenderText_Shaded() Failed with: %s\n", TTF_GetError());
        return;
    }

    // Convert the surface to a texture
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(sdl_renderer, textSurface);
    if (!textTexture) {
        printf("[ERROR] SDL_CreateTextureFromSurface() Failed with: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    // Query the texture to get its width and height
    int text_width, text_height;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &text_width, &text_height);

    // Define the destination rectangle for the texture
    SDL_Rect dest_rect = {x, y, text_width, text_height};

    // Copy the texture to the renderer
    SDL_RenderCopy(sdl_renderer, textTexture, nullptr, &dest_rect);

    // Clean up the texture and surface
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}


void renderer::init(world_representation world) {
    printf("hi from printf\n");
    cout << "hi from cout\n";
    renderable_height = world.height - invisible_height_margin;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Tetris Challenge",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              world.width * normal_cell_size + grid_margin_x * 2,
                              renderable_height * normal_cell_size + grid_margin_y * 2,
                              SDL_WINDOW_SHOWN
    );
    sdl_renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Init();
}

void renderer::begin_drawing() {
    SDL_RenderClear(sdl_renderer);
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
}

void renderer::draw_world(world_representation world) {
    //fill the borders
    SDL_Rect border_rect;
    border_rect.h = renderable_height * normal_cell_size;
    border_rect.w = world.width * normal_cell_size;
    border_rect.x = grid_margin_x;
    border_rect.y = grid_margin_y;
    SDL_RenderDrawRect(sdl_renderer, &border_rect);

    for (int y = invisible_height_margin; y < world.height; y++) {
        for (int x = 0; x < world.width; x++) {
            draw_cell(x, y - invisible_height_margin, world.grid[x][y]);
        }
    }
}

void renderer::show_side_rect_stuff(int score, tetromino next_tetromino) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_Rect border_rect;
    border_rect.h = side_rect_height;
    border_rect.w = side_rect_width;
    border_rect.x = 10;
    border_rect.y = grid_margin_y;
    SDL_RenderDrawRect(sdl_renderer, &border_rect);
    draw_text_to_renderer("score: " + to_string(score), 25, 20, 50, color_white);

    //show next tetromino
    if (next_tetromino.type == last)
        return;


    draw_text_to_renderer("next:", 25, 20, 80, color_white);

    for (const auto &coord: next_tetromino.get_positions()) {
        draw_block(side_rect_width / 2 + coord[0] * small_cell_size,
                   140 + coord[1] * small_cell_size,
                   next_tetromino.color,
                   small_cell_size
        );
    }
}

void renderer::show_game_result(int score) {
    SDL_Rect rect;
    rect.h = 200;
    rect.w = 200;
    rect.x = SDL_GetWindowSurface(window)->w / 2 - 100;
    rect.y = SDL_GetWindowSurface(window)->h / 2 - 100;
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(sdl_renderer, &rect);
    rect.x++;
    rect.y++;
    rect.w = 198;
    rect.h = 198;
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(sdl_renderer, &rect);
    draw_text_to_renderer(
            "score: " + to_string(score),
            25,
            SDL_GetWindowSurface(window)->w / 2 - 50,
            SDL_GetWindowSurface(window)->h / 2 - 50,
            color_white);

    draw_text_to_renderer(
            "best score: " + to_string(score),
            25,
            SDL_GetWindowSurface(window)->w / 2 - 80,
            SDL_GetWindowSurface(window)->h / 2,
            color_white);

    draw_text_to_renderer(
            "[Space] to restart",
            15,
            SDL_GetWindowSurface(window)->w / 2 - 60,
            SDL_GetWindowSurface(window)->h / 2 + 50,
            color_white);
}

void renderer::end_drawing() {
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(sdl_renderer);
}

void renderer::get_color_of_cell(tetromino_color col, Uint8 &color_r, Uint8 &color_g, Uint8 &color_b) {
    color_r = 0;
    color_g = 0;
    color_b = 0;
    switch (col) {
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

void renderer::draw_cell(const int x, const int y, world_cell cell) {
    if (cell.filled)
        draw_block(grid_margin_x + x * normal_cell_size,
                   grid_margin_y + y * normal_cell_size,
                   cell.color,
                   normal_cell_size
        );
}

void renderer::draw_block(int x, int y, tetromino_color color, int cell_size) {
    Uint8 color_r = 255;
    Uint8 color_g = 255;
    Uint8 color_b = 255;
    SDL_SetRenderDrawColor(sdl_renderer, color_r, color_g, color_b, 255);
    drawing_rct.h = cell_size;
    drawing_rct.w = cell_size;
    drawing_rct.x = x;
    drawing_rct.y = y;
    SDL_RenderDrawRect(sdl_renderer, &drawing_rct);

    get_color_of_cell(color, color_r, color_g, color_b);
    SDL_SetRenderDrawColor(sdl_renderer, color_r, color_g, color_b, 255);
    drawing_rct.h -= cell_border_thickness * 2;
    drawing_rct.w -= cell_border_thickness * 2;
    drawing_rct.x += cell_border_thickness;
    drawing_rct.y += cell_border_thickness;
    SDL_RenderFillRect(sdl_renderer, &drawing_rct);
}