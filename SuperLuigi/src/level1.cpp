//
// Created by Vandebosch Remy on 27/11/2018.
//

#include "level1.h"

std::vector<Background *> level1::backgrounds() {
    return {bg.get()};
}

void level1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager> (new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(background_simplePal,
                                                                  sizeof(background_simplePal)));

    bg = std::unique_ptr<Background>(new Background(1, background_simpleTiles, sizeof(background_simpleTiles), background_simpleMap, sizeof(background_simpleMap)));
    bg.get()->useMapScreenBlock(16);
}

std::vector<Sprite *> level1::sprites() {
    return{};
}

void level1::tick(u16 keys) {}