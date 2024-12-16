#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <locale>
#include <codecvt>

#include "globals.cpp"

#include "click_sound.h"
#include "success_sound.h"

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
        "Paint-doku",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        screenWidth / 2, screenHeight / 2,
        SDL_WINDOW_SHOWN // Use SHOWN instead of FULLSCREEN for windowed mode
    );
    if (!Globals::window) return false;

    Globals::renderer = SDL_CreateRenderer(Globals::window, -1, SDL_RENDERER_ACCELERATED);
    Globals::font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 24);
    if (!Globals::renderer || !Globals::font) return false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return false;
    }
    Globals::success_sound = Mix_QuickLoad_WAV(success_sound);
    Globals::click_sound = Mix_QuickLoad_WAV(click_sound);
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
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}
