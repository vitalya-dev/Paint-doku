#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
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

std::unordered_map<std::string, SDL_Texture*> numberTextures;
std::string generateKey(int number, SDL_Color color) {
    return std::to_string(number) + "_" + 
           std::to_string(color.r) + "_" + 
           std::to_string(color.g) + "_" + 
           std::to_string(color.b);
}

SDL_Texture* getOrCreateTexture(SDL_Renderer* renderer, TTF_Font* font, int number, SDL_Color color) {
    std::string key = generateKey(number, color);

    // Check if texture already exists
    if (numberTextures.find(key) != numberTextures.end()) {
        return numberTextures[key];
    }

    // Create new texture
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(number).c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Store texture in the map
    numberTextures[key] = textTexture;
    return textTexture;
}



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
    return grid_to_hash() == "86da585336203b69";
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

SDL_Color darker_color(const SDL_Color& color, int amount = 50) {
    SDL_Color darker_color = color;
    darker_color.r = std::max(0, color.r - amount);
    darker_color.g = std::max(0, color.g - amount);
    darker_color.b = std::max(0, color.b - amount);
    return darker_color;
}
SDL_Color brighter_color(const SDL_Color& color, int amount = 50) {
    SDL_Color brighter_color = color;
    brighter_color.r = std::min(255, color.r + amount);
    brighter_color.g = std::min(255, color.g + amount);
    brighter_color.b = std::min(255, color.b + amount);
    return brighter_color;
}

SDL_Color adjust_text_color(const SDL_Color& fill_color, int adjustment_amount = 100) {
    // Calculate perceived brightness
    int brightness = static_cast<int>(0.299 * fill_color.r + 0.587 * fill_color.g + 0.114 * fill_color.b);

    // Adjust text color
    if (brightness < 64) {
        // Background is dark, make text brighter
        return brighter_color(fill_color, adjustment_amount);
    } else {
        // Background is very bright, make text darker
        return darker_color(fill_color, adjustment_amount);
    } 
}

// Render the grid and cell numbers
void renderGrid(SDL_Renderer* renderer, TTF_Font* font, bool draw_borders=true, bool draw_numbers=true) {
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
            if (draw_numbers && grid[row][col].number > 0) {
                SDL_Color text_color = grid[row][col].number_color;
                if (colorDistance(grid[row][col].fill_color, text_color) == 0)
                    text_color = adjust_text_color(grid[row][col].fill_color);
                 // Get or create texture
                SDL_Texture* textTexture = getOrCreateTexture(renderer, font, grid[row][col].number, text_color);

                // Get texture dimensions
                int texWidth, texHeight;
                SDL_QueryTexture(textTexture, NULL, NULL, &texWidth, &texHeight);

                SDL_Rect textRect = {
                    col * CELL_SIZE + (CELL_SIZE - texWidth) / 2,
                    row * CELL_SIZE + (CELL_SIZE - texHeight) / 2,
                    texWidth,
                    texHeight
                };
                SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
            }
        }
    }
}

void setCellColor(int row, int col, SDL_Color color) {
    grid[row][col].fill_color = color;
}

SDL_Color getCellColor(int row, int col) {
    return grid[row][col].fill_color;
}

void handleGridClick(int mouseX, int mouseY, SDL_Color selectedColor) {
    int col = mouseX / CELL_SIZE;
    int row = mouseY / CELL_SIZE;

    if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
        const SDL_Color currentColor = getCellColor(row, col);
        if (colorDistance(currentColor, WHITE) == 0) {
            setCellColor(row, col, selectedColor);
        } else {
            setCellColor(row, col, WHITE);
        }
    }
}
