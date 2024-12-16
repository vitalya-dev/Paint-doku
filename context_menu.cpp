#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "colors.cpp"
#include "globals.cpp"

const int MENU_WIDTH = 45; 
const int MENU_ITEM_HEIGHT = 45;

const SDL_Color MENU_BG_COLOR = {200, 200, 200, 255};
const SDL_Color MENU_HOVER_COLOR = {180, 180, 250, 255};

struct MenuItem {
    std::string label;
    SDL_Color color;
};

std::vector<MenuItem> contextMenuItems = {
    {"Fill Black", BLACK},
    {"Fill Red", RED},
    {"Fill Green", GREEN},
    {"Fill Blue", BLUE},
    {"Fill Orange", ORANGE},
};


int getHoveredMenuItemIndex(int mouseX, int mouseY) {
    SDL_Rect menuRect = {Globals::menuX, Globals::menuY, MENU_WIDTH, static_cast<int>(contextMenuItems.size()) * MENU_ITEM_HEIGHT};

    // Check if the mouse is within the menu bounds
    if (mouseX >= menuRect.x && mouseX < menuRect.x + menuRect.w &&
        mouseY >= menuRect.y && mouseY < menuRect.y + menuRect.h) {
        // Calculate which item is hovered
        int index = (mouseY - menuRect.y) / MENU_ITEM_HEIGHT;
        return index;
    }
    // Return -1 if no item is hovered
    return -1;
}

MenuItem* getHoveredMenuItem(int mouseX, int mouseY) {
    int index = getHoveredMenuItemIndex(mouseX, mouseY);
    if (index != -1 && index < static_cast<int>(contextMenuItems.size())) {
        return &contextMenuItems[index];
    }
    return nullptr;
}

// Render the context menu
void renderContextMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Rect menuRect = {Globals::menuX, Globals::menuY, MENU_WIDTH, static_cast<int>(contextMenuItems.size()) * MENU_ITEM_HEIGHT};
    SDL_SetRenderDrawColor(renderer, MENU_BG_COLOR.r, MENU_BG_COLOR.g, MENU_BG_COLOR.b, MENU_BG_COLOR.a);
    SDL_RenderFillRect(renderer, &menuRect);

    int hoveredIndex = getHoveredMenuItemIndex(Globals::mouseX, Globals::mouseY);

    for (int i = 0; i < static_cast<int>(contextMenuItems.size()); ++i) {
        SDL_Rect itemRect = {Globals::menuX, Globals::menuY + i * MENU_ITEM_HEIGHT, MENU_WIDTH, MENU_ITEM_HEIGHT};
        SDL_Color bgColor = (i == hoveredIndex) ? MENU_HOVER_COLOR : MENU_BG_COLOR;
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &itemRect);

        // Draw the color swatch
        SDL_Rect colorRect = {Globals::menuX + 4, Globals::menuY + i * MENU_ITEM_HEIGHT + 4, MENU_WIDTH - 2 *4, MENU_ITEM_HEIGHT - 2 * 4};
        SDL_Color color = contextMenuItems[i].color;
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer, &colorRect);

        // Optional: Add a border around the color swatch for better visibility
        // Draw a bolder border around the color swatch
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black border
        for (int j = 0; j < 3; ++j) { // Loop for thickness (3 pixels)
            SDL_Rect borderRect = {colorRect.x + j, colorRect.y + j, colorRect.w - 2 * j, colorRect.h - 2 * j};
            SDL_RenderDrawRect(renderer, &borderRect);
        }
    }
}
