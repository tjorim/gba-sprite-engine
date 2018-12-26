//
// Created by Wout Briels on 26/12/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level2Scene.h"
#include "BGdata_Level2Scene.h"


std::vector<Background *> Level2Scene::backgrounds() {
    return {};
}

std::vector<Sprite *> Level2Scene::sprites() {
    return{};
}

void Level2Scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette));
}

void Level2Scene::tick(u16 keys) {}