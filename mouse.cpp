#pragma once

#include "globals.cpp"

// Handle left mouse button click
void handleLeftClick() {
    if (Globals::menuVisible) {
        // Check if the click is within the bounds of the context menu
        int menuHeight = contextMenuItems.size() * MENU_ITEM_HEIGHT;

        if (mouseX >= menuX && mouseX <= menuX + MENU_WIDTH &&
                mouseY >= menuY && mouseY <= menuY + menuHeight) {

            int itemIndex = (mouseY - menuY) / MENU_ITEM_HEIGHT;
            if (itemIndex >= 0 && itemIndex < static_cast<int>(contextMenuItems.size())) {
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
    Globals::menuVisible = true;
    Globals::menuX = mouseX;
    Globals::menuY = mouseY;
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