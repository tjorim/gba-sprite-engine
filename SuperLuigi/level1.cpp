//
// Created by Vandebosch Remy on 27/11/2018.
//

#include "level1.h"

std::vector<Background *> level1::backgrounds() {
    return {bg.get()};
}

void level1::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(background_simplePal,
                                                                  sizeof(background_simplePal)));

    bg = std::unique_ptr<Background>(new Background(1, background_simpleTiles, sizeof(background_simpleTiles), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);
}