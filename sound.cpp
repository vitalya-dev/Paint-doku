#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>

void playMusic(Mix_Music* music, int loops) {
    static Mix_Music* currentMusic = nullptr;

    if (Mix_PlayingMusic() && currentMusic == music) {
        return;
    }
    if (Mix_PlayMusic(music, loops) == -1) {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        currentMusic = music;
    }
}