#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "colors.cpp"

namespace Globals {
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	TTF_Font* font = nullptr;


	bool menuVisible = false;
	int menuX = 0, menuY = 0;
	int mouseX = 0, mouseY = 0;
	SDL_Color selectedColor = BLACK;

	bool quit = false;
}