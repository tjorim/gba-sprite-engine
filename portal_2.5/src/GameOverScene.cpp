//
// Created by Leander on 24/12/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "GameOverScene.h"
#include "Scene_sprites.h"
#include "Level1_background.h"
#include "LevelScene.h"

std::vector<Sprite *> GameOverScene::sprites() {
    return {cake.get()};
}

std::vector<Background *> GameOverScene::backgrounds() {
    return {bg.get()};
}


void GameOverScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;

    cake = builder
            .withData(CakeTiles, sizeof(CakeTiles))
            .withSize(SIZE_16_16)
            .withLocation(110,70)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    TextStream::instance().setText(std::string("Test Complete"), 5, 8);

}

void GameOverScene::tick(u16 keys) {

}