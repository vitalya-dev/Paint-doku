#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <locale>
#include <codecvt>

#include "globals.cpp"

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

    Globals::window = SDL_CreateWindow(
        "Link-Up Paint-doku",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth / 2, screenHeight / 2,
        SDL_WINDOW_SHOWN // Use SHOWN instead of FULLSCREEN for windowed mode
    );
    if (!Globals::window) return false;

    Globals::renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
    Globals::font = TTF_OpenFont("Comic Sans MS.ttf", 24);
    if (!Globals::renderer || !Globals::font) return false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return false;
    }
    Globals::success_sound = Mix_LoadMUS("success.wav");
    Globals::click_sound = Mix_LoadWAV("click.wav");
    if (!Globals::success_sound && !Globals::click_sound) {
        return false;
    }

    return true;
}

// Cleanup resources
void cleanup() {
    TTF_CloseFont(Globals::font);
    SDL_DestroyRenderer(Globals::renderer);
    SDL_DestroyWindow(Globals::window);
    Mix_FreeMusic(Globals::success_sound);
    Mix_FreeChunk(Globals::click_sound);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
