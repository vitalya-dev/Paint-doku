#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <locale>

// Constants
const int GRID_SIZE = 20;
const int CELL_SIZE = 30;
const int MENU_WIDTH = 120;
const int MENU_ITEM_HEIGHT = 30;

const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color ORANGE = {255, 165, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};  // Default for empty or uncolored cells
const SDL_Color GRAY = {128, 128, 128, 255};
const SDL_Color MENU_BG_COLOR = {200, 200, 200, 255};
const SDL_Color MENU_HOVER_COLOR = {180, 180, 250, 255};

// Struct Definitions
struct Cell {
    int number;
    SDL_Color number_color;
    SDL_Color fill_color;
};

struct MenuItem {
    std::string label;
    SDL_Color color;
};


// Global Variables
bool menuVisible = false;
int menuX = 0, menuY = 0;
int mouseX = 0, mouseY = 0;
SDL_Color selectedColor = BLACK;
std::vector<MenuItem> contextMenuItems = {
    {"Fill Black", BLACK},
    {"Fill Red", RED},
    {"Fill Green", GREEN},
    {"Fill Blue", BLUE},
    {"Fill Orange", ORANGE},
    {"Exit", BLACK} // Exit menu color
};

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

bool quit = false;

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


SDL_Color invert_color(SDL_Color color) {
    SDL_Color inverted_color = color;
    inverted_color.r = 255 - inverted_color.r;
    inverted_color.g = 255 - inverted_color.g;
    inverted_color.b = 255 - inverted_color.b;
    return inverted_color;
}

// Helper function to calculate color distanc
int colorDistance(SDL_Color color1, SDL_Color color2) {
    int dr = color1.r - color2.r;
    int dg = color1.g - color2.g;
    int db = color1.b - color2.b;
    return dr * dr + dg * dg + db * db;
}

std::wstring utf8_to_wstring(const std::string& utf8str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(utf8str);
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
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

// Render the grid and cell numbers
void renderGrid(SDL_Renderer* renderer, TTF_Font* font) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        for (int col = 0; col < GRID_SIZE; ++col) {
            SDL_Rect cellRect = {col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
            SDL_SetRenderDrawColor(renderer, grid[row][col].fill_color.r, grid[row][col].fill_color.g, grid[row][col].fill_color.b, 255);
            SDL_RenderFillRect(renderer, &cellRect);

            // Draw cell borders
            SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, GRAY.a);
            SDL_RenderDrawRect(renderer, &cellRect);

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


// Render the context menu
void renderContextMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect menuRect = {menuX, menuY, MENU_WIDTH, contextMenuItems.size() * MENU_ITEM_HEIGHT};
    SDL_SetRenderDrawColor(renderer, MENU_BG_COLOR.r, MENU_BG_COLOR.g, MENU_BG_COLOR.b, MENU_BG_COLOR.a);
    SDL_RenderFillRect(renderer, &menuRect);

    for (int i = 0; i < contextMenuItems.size(); ++i) {
        SDL_Rect itemRect = {menuX, menuY + i * MENU_ITEM_HEIGHT, MENU_WIDTH, MENU_ITEM_HEIGHT};
        SDL_SetRenderDrawColor(renderer, (mouseX >= itemRect.x && mouseX < itemRect.x + itemRect.w && mouseY >= itemRect.y && mouseY < itemRect.y + itemRect.h) ? MENU_HOVER_COLOR.r : MENU_BG_COLOR.r, MENU_BG_COLOR.g, MENU_BG_COLOR.b, MENU_BG_COLOR.a);
        SDL_RenderFillRect(renderer, &itemRect);

        SDL_Surface* textSurface = TTF_RenderText_Solid(font, contextMenuItems[i].label.c_str(), BLACK);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {menuX + 5, menuY + i * MENU_ITEM_HEIGHT + 5, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(textSurface);
    }
}

// Set cell color with bounds checking
void setCellColor(int row, int col, SDL_Color color) {
    grid[row][col].fill_color = color;
}

// Handle left mouse button click
void handleLeftClick() {
    if (menuVisible) {
        // Check if the click is within the bounds of the context menu
        int menuHeight = contextMenuItems.size() * MENU_ITEM_HEIGHT;

        if (mouseX >= menuX && mouseX <= menuX + MENU_WIDTH &&
                mouseY >= menuY && mouseY <= menuY + menuHeight) {

            int itemIndex = (mouseY - menuY) / MENU_ITEM_HEIGHT;
            if (itemIndex >= 0 && itemIndex < contextMenuItems.size()) {
                if (contextMenuItems[itemIndex].label == "Exit") {
                    quit = true;
                } else {
                    selectedColor = contextMenuItems[itemIndex].color;
                }
            }
        }
        // Close the menu after handling the click
        menuVisible = false;
    } else {
        int col = mouseX / CELL_SIZE;
        int row = mouseY / CELL_SIZE;
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if (col >= 0 && col < GRID_SIZE && row >= 0 && row < GRID_SIZE) {
            setCellColor(row, col, (state[SDL_SCANCODE_LCTRL] || state[SDL_SCANCODE_RCTRL]) ? WHITE : selectedColor);
        }
    }
}

// Handle right mouse button click to open the context menu
void handleRightClick() {
    menuVisible = true;
    menuX = mouseX;
    menuY = mouseY;
}

// Handle mouse click events
void handleMouseClick(SDL_Event* event) {
    mouseX = event->button.x;
    mouseY = event->button.y;
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_RIGHT) {
            handleRightClick();
        } else if (event->button.button == SDL_BUTTON_LEFT) {
            handleLeftClick();
        }
    }
}

// Cleanup resources
void cleanup() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

void renderText(const std::string& text, int x, int y, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}


void play_tutorial() {
    SDL_RenderSetLogicalSize(renderer, 900, 600);
    bool tutorialRunning = true;
    SDL_Event e;
    // Tutorial text split into lines
    std::vector<std::wstring> tutorialLines = {
        utf8_to_wstring("Привет!"),
        utf8_to_wstring("В этой игре вы будете раскрашивать клетки цветами."),
        utf8_to_wstring("Число в клетке показывает, сколько клеток одного цвета соединены линией."),
        utf8_to_wstring("Линии могут быть только горизонтальными или вертикальными."),
        utf8_to_wstring("Линии не должны пересекаться друг с другом или самими собой."),
        utf8_to_wstring("Чтобы выбрать цвет, используйте контекстное меню."),
        utf8_to_wstring("Начнем!")
    };


    size_t currentLine = 0;
    size_t charIndex = 0;

    // Clear the screen once and set the background color
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    while (tutorialRunning) {
    	SDL_RenderClear(renderer);
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                tutorialRunning = false;
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                if (charIndex < tutorialLines[currentLine].size()) {
                    charIndex = tutorialLines[currentLine].size();
                } else {
                    currentLine++;
                    charIndex = 0;
                }
                if (currentLine >= tutorialLines.size()) {
                    tutorialRunning = false;
                    break;
                }
            }
        }
        if (!tutorialRunning)
        	break;

        if (currentLine < tutorialLines.size() && charIndex < tutorialLines[currentLine].size()) {
            charIndex++;
        }
        // Render the current line being typed out
	    for (size_t i = 0; i <= currentLine; ++i) {
	        int text_width, text_height;
	        std::string line_text = wstring_to_utf8(tutorialLines[i].substr(0, i == currentLine ? charIndex : tutorialLines[i].size()));
	        std::string line_text_full = wstring_to_utf8(tutorialLines[i]);
	        TTF_SizeUTF8(font, line_text_full.c_str(), &text_width, &text_height);
	        int x_position = (900 - text_width) / 2;
	        int y_position = 50 + i * (text_height + 10);
            std::cout << text_width << std::endl;
	        renderText(line_text, x_position > 0 ? x_position : 0, y_position, BLACK);
	    }
        SDL_RenderPresent(renderer);
        SDL_Delay(10); // Adjust the delay to control the typewriting speed
    }
}


void play_game() {
    SDL_RenderSetLogicalSize(renderer, 600, 600);
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_p) {
                        std::cout << grid_to_string() << std::endl;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEMOTION:
                    handleMouseClick(&e);
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        renderGrid(renderer, font);
        if (menuVisible)
            renderContextMenu(renderer, font);
        SDL_RenderPresent(renderer);
    }
}

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() == -1) {
        return false;
    }

    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        return false;
    }
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    window = SDL_CreateWindow(
        "Link-Up Paint-doku",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth / 2, screenHeight / 2,
        SDL_WINDOW_SHOWN // Use SHOWN instead of FULLSCREEN for windowed mode
    );
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    font = TTF_OpenFont("Comic Sans MS.ttf", 24);
    if (!renderer || !font) return false;

    return true;
}


int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Error occured: " << SDL_GetError() << std::endl;
        return -1;
    }
    play_tutorial();
    play_game();
    cleanup();
    return 0;
}
