//
// Created by Wout Briels on 26/12/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level2Scene.h"
#include "BGdata_Level2Scene.h"

#include "Sprite.h"

std::vector<Background *> Level2Scene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> Level2Scene::sprites() {
    return{
        player.get()
    };
}

void Level2Scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;

    player = builder
            .withData(player_data, sizeof(player_data))
            .withSize(SIZE_16_32)
            .withAnimated(4, 5)
            .withLocation(10, GBA_SCREEN_HEIGHT - 32 - 5*16)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);
}

void Level2Scene::tick(u16 keys) {
    bg.get()->scroll(bgX, bgY);
}