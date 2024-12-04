#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

// Constants


const int MENU_WIDTH = 120;
const int MENU_ITEM_HEIGHT = 30;

const SDL_Color MENU_BG_COLOR = {200, 200, 200, 255};
const SDL_Color MENU_HOVER_COLOR = {180, 180, 250, 255};



struct MenuItem {
    std::string label;
    SDL_Color color;
};



// Global state for particle system
Mix_Chunk* g_successSound = nullptr;

// Global Variables

std::vector<MenuItem> contextMenuItems = {
    {"Fill Black", BLACK},
    {"Fill Red", RED},
    {"Fill Green", GREEN},
    {"Fill Blue", BLUE},
    {"Fill Orange", ORANGE},
    {"Exit", BLACK} // Exit menu color
};














// Render the context menu
void renderContextMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect menuRect = {menuX, menuY, MENU_WIDTH, static_cast<int>(contextMenuItems.size()) * MENU_ITEM_HEIGHT};
    SDL_SetRenderDrawColor(renderer, MENU_BG_COLOR.r, MENU_BG_COLOR.g, MENU_BG_COLOR.b, MENU_BG_COLOR.a);
    SDL_RenderFillRect(renderer, &menuRect);

    for (int i = 0; i < static_cast<int>(contextMenuItems.size()); ++i) {
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


std::wstring utf8_to_wstring(const std::string& utf8str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(utf8str);
}

std::string wstring_to_utf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
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

    // Tutorial text split into lines
    std::vector<std::wstring> tutorialLines = {
        utf8_to_wstring("Привет!"),
        utf8_to_wstring("В этой игре вы будете раскрашивать клетки цветами."),
        utf8_to_wstring("Число в клетке показывает, сколько клеток одного цвета соединены линией."),
        utf8_to_wstring("Линии могут быть только горизонтальными или вертикальными."),
        utf8_to_wstring("Линии не должны пересекаться друг с другом или самими собой."),
        utf8_to_wstring("Чтобы выбрать цвет, используйте контекстное меню."),
        utf8_to_wstring("Что бы стереть цвет, используйте клавишу ctrl."),
        utf8_to_wstring("Примеры:"),
        utf8_to_wstring(" "),
        utf8_to_wstring(" "),
        utf8_to_wstring("Приступим")
    };

    // Utility to load textures
    auto loadTexture = [](const std::string& filePath) -> SDL_Texture* {
        SDL_Surface* surface = SDL_LoadBMP(filePath.c_str());
        if (!surface) return nullptr;
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        return texture;
    };

    SDL_Texture* tutorialImage1 = loadTexture("tutorial_image1.bmp");
    SDL_Texture* tutorialImage2 = loadTexture("tutorial_image2.bmp");

    // Variables for typewriting effect and control
    size_t currentLine = 0;
    size_t charIndex = 0;
    bool tutorialRunning = true;
    SDL_Event event;

    // Utility to render text and images
    auto renderTextAndImages = [&](const std::wstring& line, size_t displayCount, int lineIndex) {
        std::string utf8Text = wstring_to_utf8(line);
        int textWidth, textHeight;
        if (TTF_SizeUTF8(font, utf8Text.c_str(), &textWidth, &textHeight) == 0) {
            textHeight += 12;
            int x = (900 - textWidth) / 2;
            renderText(wstring_to_utf8(line.substr(0, displayCount)), std::max(x, 0), 50 + lineIndex * textHeight, BLACK);
        }

        // Render tutorial images based on lineIndex
        if (lineIndex >= 8) {
            SDL_Rect img1Rect = {900 / 2 - 125, 50 + 8 * textHeight - 10, 100, 100};
            SDL_RenderCopy(renderer, tutorialImage1, nullptr, &img1Rect);
        }
        if (lineIndex >= 9) {
            SDL_Rect img2Rect = {900 / 2 + 25, 50 + 8 * textHeight - 10, 100, 100};
            SDL_RenderCopy(renderer, tutorialImage2, nullptr, &img2Rect);
        }
    };

    // Event handling
    auto handleEvents = [&]() {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                tutorialRunning = false;
                quit = true;
            } else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                if (charIndex < tutorialLines[currentLine].size()) {
                    charIndex = tutorialLines[currentLine].size(); // Skip to the end of the line
                } else {
                    currentLine++;
                    charIndex = 0;
                }
                if (currentLine >= tutorialLines.size()) {
                    tutorialRunning = false;
                }
            }
        }
    };

    // Main tutorial loop
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    while (tutorialRunning) {
        handleEvents();
        if (!tutorialRunning)
            break;

        // Typewriting effect
        if (currentLine < tutorialLines.size() && charIndex < tutorialLines[currentLine].size()) {
            charIndex++;
        }

        // Clear screen and render text/images
        SDL_RenderClear(renderer);
        for (size_t i = 0; i <= currentLine; ++i) {
            size_t displayCount = (i == currentLine) ? charIndex : tutorialLines[i].size();
            renderTextAndImages(tutorialLines[i], displayCount, i);
        }
        SDL_RenderPresent(renderer);

        SDL_Delay(10); // Adjust typewriting speed
    }

    // Cleanup
    if (tutorialImage1) SDL_DestroyTexture(tutorialImage1);
    if (tutorialImage2) SDL_DestroyTexture(tutorialImage2);
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
                        std::cout << grid_to_hash() << std::endl;
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

void play_celebration() {
    SDL_RenderSetLogicalSize(renderer, 600, 600);
    if (g_particles.empty()) {
        initParticleSystem();
    }
    createCelebrationParticles(600 / 2, 600 / 2);

    // Render and update particles in a loop for a short duration
    const Uint32 celebrationDuration = 2000; // 2 seconds
    Uint32 startTime = SDL_GetTicks();
    Uint32 currentTime;
    SDL_Event event;

    while (true) {
        // Calculate elapsed time
        currentTime = SDL_GetTicks();
        Uint32 elapsedTime = currentTime - startTime;

        // Break the loop after the celebration duration
        if (elapsedTime >= celebrationDuration) {
            break;
        }

        // Handle events to prevent the application from freezing
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
                return;
            }
        }

        // Update particles
        float deltaTime = elapsedTime / 1000.0f; // Convert milliseconds to seconds
        updateParticles(deltaTime);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render particles
        renderParticles(renderer);

        // Present the rendered frame
        SDL_RenderPresent(renderer);

        // Delay to control frame rate
        SDL_Delay(16); // ~60 FPS
    }
    cleanupParticleSystem();
}




int main(int argc, char* argv[]) {
    if (!init()) {
        std::cerr << "Error occured: " << SDL_GetError() << std::endl;
        return -1;
    }
    play_celebration();
    play_tutorial();
    play_game();
    //play_celebration();
    cleanup();
    return 0;
}
