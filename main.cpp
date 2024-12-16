#include <iostream>

#include "init.cpp"
#include "grid.cpp"
#include "mouse.cpp"
#include "sound.cpp"

enum GameState {
    GAMEPLAY,
    SOLVED
};

// Helper function to handle events
void processEvents(SDL_Event& e, GameState game_state) {
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                Globals::quit = true;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_p) {
                    std::cout << grid_to_hash() << std::endl;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEMOTION:
                if (game_state == GAMEPLAY) {
                    handleMouseClick(&e);
                }
                break;
        }
    }
}

// Helper function to render the frame
void renderFrame(GameState game_state) {
    SDL_SetRenderDrawColor(Globals::renderer, 255, 255, 255, 255);
    SDL_RenderClear(Globals::renderer);
    switch (game_state) {
    case GAMEPLAY:
        renderGrid(Globals::renderer, Globals::font, true, true);
        if (Globals::menuVisible) {
            renderContextMenu(Globals::renderer, Globals::font);
        }
        break;
    case SOLVED:
        renderGrid(Globals::renderer, Globals::font, false, false);
        if (Globals::menuVisible) {
            renderContextMenu(Globals::renderer, Globals::font);
        }
        break;
    }
    SDL_RenderPresent(Globals::renderer);
}


int main(int argc, char* argv[]) {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

	if (!init()) {
        std::cerr << "Error occured: " << SDL_GetError() << std::endl;
        return -1;
    }
    std::cout << "frameDelay: " << frameDelay << std::endl;

    SDL_RenderSetLogicalSize(Globals::renderer, 600, 600);
    SDL_Event e;
    GameState gameState = GAMEPLAY; // Initial state of the game

    while (!Globals::quit) {
        Uint32 frameStart = SDL_GetTicks();
        processEvents(e, gameState);
        switch (gameState) {
        case GAMEPLAY:
            if (is_grid_solved()) {
                playSoundEffect(Globals::success_sound); // Play the song once
                gameState = SOLVED;
            }
            break;
        case SOLVED:
            break;
        }
        renderFrame(gameState);

        Uint32 frameTime = SDL_GetTicks() - frameStart;
        std::cout << "Frame time: " << frameTime << std::endl;
        if (frameDelay > frameTime) {
            std::cout << "Delay: " << frameDelay << std::endl;
            SDL_Delay(frameDelay - frameTime);
        }

    }
	return 0;
}