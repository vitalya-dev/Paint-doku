#include <iostream>

#include "init.cpp"
#include "grid.cpp"
#include "mouse.cpp"


int main(int argc, char* argv[]) {
	if (!init()) {
        std::cerr << "Error occured: " << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_RenderSetLogicalSize(Globals::renderer, 600, 600);
    SDL_Event e;
    while (!Globals::quit) {
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
                    handleMouseClick(&e);
                    break;
            }
        }
        SDL_SetRenderDrawColor(Globals::renderer, 255, 255, 255, 255);
        SDL_RenderClear(Globals::renderer);
        renderGrid(Globals::renderer, Globals::font);
        SDL_RenderPresent(Globals::renderer);
    }
	return 0;
}