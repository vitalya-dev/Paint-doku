#pragma once

#include <SDL2/SDL_mixer.h>
#include <iostream>


void playSoundEffect(Mix_Chunk* sound) {
    if (sound && Mix_PlayChannel(-1, sound, 0) == -1) {
        std::cerr << "Failed to play sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
}