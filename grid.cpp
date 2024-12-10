#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "colors.cpp"

const int GRID_SIZE = 20;
const int CELL_SIZE = 30;

// Struct Definitions
struct Cell {
    int number;
    SDL_Color number_color;
    SDL_Color fill_color;
};

Cell grid[GRID_SIZE][GRID_SIZE] = {
    // Row 1
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {9, RED, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {2, RED, WHITE}, {2, RED, WHITE}, {2, BLACK, WHITE},
        {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}
    },
    // Row 2
    {   {4, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {10, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE},
        {5, RED, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}
    },
    // Row 3
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {9, BLACK, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}
    },
    // Row 4
    {   {0, WHITE, WHITE}, {2, ORANGE, WHITE}, {2, ORANGE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {9, RED, WHITE}, {3, BLACK, WHITE},
        {5, RED, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}
    },
    // Row 5
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {10, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}
    },
    // Row 6
    {   {4, BLACK, WHITE}, {2, ORANGE, WHITE}, {2, ORANGE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}
    },
    // Row 7
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {4, RED, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE},
        {0, WHITE, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {9, BLACK, WHITE}, {0, WHITE, WHITE}

    },
    // Row 8
    {   {10, BLACK, WHITE}, {0, WHITE, WHITE}, {4, RED, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {9, BLACK, WHITE}, {2, BLACK, WHITE},
        {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}

    },
    // Row 9
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}

    },
    // Row 10
    {   {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {4, RED, WHITE}, {0, WHITE, WHITE}, {6, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {6, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {10, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}

    },
    // Row 11
    {   {0, WHITE, WHITE}, {2, BLACK, WHITE}, {4, RED, WHITE}, {9, BLACK, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE},  {0, WHITE, WHITE}

    },
    // Row 12
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE},
        {3, BLACK, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}

    },
    // Row 13
    {   {10, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {9, BLACK, WHITE}, {3, BLACK, WHITE}

    },
    // Row 14
    {   {9, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE},
        {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}
    },
    // Row 15
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {10, BLACK, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}, {2, BLACK, WHITE},
        {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {3, BLACK, WHITE}
    },
    // Row 16
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {7, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {10, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {6, BLACK, WHITE}, {0, WHITE, WHITE}
    },
    // Row 17
    {   {0, WHITE, WHITE}, {7, BLACK, WHITE}, {2, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {10, BLACK, WHITE}, {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE},
        {0, WHITE, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {9, GREEN, WHITE}, {7, BLACK, WHITE}, {0, WHITE, WHITE}, {7, BLACK, WHITE}, {4, GREEN, WHITE}, {0, WHITE, WHITE}
    },
    // Row 18
    {   {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {5, ORANGE, WHITE}, {2, BLACK, WHITE},
        {4, ORANGE, WHITE}, {4, BLACK, WHITE}, {0, WHITE, WHITE}, {2, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}
    },
    // Row 19
    {   {1, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {9, GREEN, WHITE}, {5, BLACK, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {2, BLACK, WHITE},
        {0, WHITE, WHITE}, {2, BLACK, WHITE}, {2, BLACK, WHITE}, {2, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {1, BLACK, WHITE}, {4, GREEN, WHITE}, {6, BLACK, WHITE}, {0, WHITE, WHITE}
    },
    // Row 20
    {   {9, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {5, ORANGE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, ORANGE, WHITE},
        {0, WHITE, WHITE}, {4, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {4, GREEN, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {0, WHITE, WHITE}, {9, GREEN, WHITE}
    }
};

std::string grid_to_string() {
    std::string grid_string = "Grid State:\n";
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid_string += "(" + 
                std::to_string(grid[row][col].number) + "," +
                std::to_string(grid[row][col].fill_color.r) + "," +
                std::to_string(grid[row][col].fill_color.g) + "," +
                std::to_string(grid[row][col].fill_color.b) + ") ";
        }
        grid_string += "\n";
    }
    return grid_string;
}

std::string grid_to_hash() {
    std::ostringstream hash_stream;
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            hash_stream << grid[row][col].number
                << grid[row][col].fill_color.r
                << grid[row][col].fill_color.g
                << grid[row][col].fill_color.b;
        }
    }
    std::hash<std::string> hasher;
    size_t hash_value = hasher(hash_stream.str());

    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << hash_value;
    return ss.str();
}

bool is_grid_solved() {
    //return grid_to_hash() == "86da585336203b69";
    return true;
}

// Helper function to calculate color distanc
int colorDistance(SDL_Color color1, SDL_Color color2) {
    int dr = color1.r - color2.r;
    int dg = color1.g - color2.g;
    int db = color1.b - color2.b;
    return dr * dr + dg * dg + db * db;
}


SDL_Color invert_color(SDL_Color color) {
    SDL_Color inverted_color = color;
    inverted_color.r = 255 - inverted_color.r;
    inverted_color.g = 255 - inverted_color.g;
    inverted_color.b = 255 - inverted_color.b;
    return inverted_color;
}

// Render the grid and cell numbers
void renderGrid(SDL_Renderer* renderer, TTF_Font* font, bool draw_borders=true) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            SDL_Rect cellRect = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_SetRenderDrawColor(renderer, grid[row][col].fill_color.r, grid[row][col].fill_color.g, grid[row][col].fill_color.b, 255);
            SDL_RenderFillRect(renderer, &cellRect);

            // Draw cell borders if requested
            if (draw_borders) {
                SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
                SDL_RenderDrawRect(renderer, &cellRect);
            }

            // Render number if greater than 0
            if (grid[row][col].number > 0) {
                SDL_Color text_color = grid[row][col].number_color;
                if (colorDistance(grid[row][col].fill_color, text_color) == 0)
                    text_color = invert_color(grid[row][col].fill_color);
                SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(grid[row][col].number).c_str(), text_color);
                SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_Rect textRect = {col * CELL_SIZE + (CELL_SIZE - textSurface->w) / 2, row * CELL_SIZE + (CELL_SIZE - textSurface->h) / 2, textSurface->w, textSurface->h};
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                SDL_DestroyTexture(textTexture);
                SDL_FreeSurface(textSurface);
            }
        }
    }
}

void setCellColor(int row, int col, SDL_Color color) {
    grid[row][col].fill_color = color;
}

void handleGridClick(int mouseX, int mouseY, SDL_Color selectedColor) {
    int col = mouseX / CELL_SIZE;
    int row = mouseY / CELL_SIZE;

    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
        const Uint8* state = SDL_GetKeyboardState(NULL);
        SDL_Color colorToSet = (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) ? WHITE : selectedColor;

        // Set the cell's color
        setCellColor(row, col, colorToSet);
    }
}
