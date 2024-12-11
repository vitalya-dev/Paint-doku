#pragma once

#include "globals.cpp"
#include "context_menu.cpp"
#include "grid.cpp"
#include "sound.cpp"

// Handle left mouse button click
void handleLeftClick() {
    playSoundEffect(Globals::click_sound);  
    if (Globals::menuVisible) {
        MenuItem* hoveredItem = getHoveredMenuItem(Globals::mouseX, Globals::mouseY);
        if (hoveredItem) {
            if (hoveredItem->label == "Exit") {
                Globals::quit = true;
            } else {
                Globals::selectedColor = hoveredItem->color;
            }
        }
        // Close the menu after handling the click
        Globals::menuVisible = false;
    } else {
        handleGridClick(Globals::mouseX, Globals::mouseY, Globals::selectedColor);
    }
}

// Handle right mouse button click to open the context menu
void handleRightClick() {
    playSoundEffect(Globals::click_sound);
    Globals::menuVisible = true;
    Globals::menuX = Globals::mouseX;
    Globals::menuY = Globals::mouseY;
}

// Handle mouse click events
void handleMouseClick(SDL_Event* event) {
    Globals::mouseX = event->button.x;
    Globals::mouseY = event->button.y;

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        if (event->button.button == SDL_BUTTON_RIGHT) {
            handleRightClick();
        } else if (event->button.button == SDL_BUTTON_LEFT) {
            handleLeftClick();
        }
    }
}
