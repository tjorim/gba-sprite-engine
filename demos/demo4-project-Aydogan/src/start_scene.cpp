//
// Created by aydoganmusa on 21.11.18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "start_scene.h"
#include "fighting_scene.h"
#include "startscreen.h"
#include "roshi.h"


std::vector<Background *> StartScene::backgrounds() {
    return {bg.get()};
}

std::vector<Sprite *> StartScene::sprites() {
    return {  animation.get() };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(roshi_palette, sizeof(roshi_palette)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(startscreenPal, sizeof(startscreenPal)));

    SpriteBuilder<Sprite> builder;

    animation = builder
            .withData(roshi_data, sizeof(roshi_data))
            .withSize(SIZE_32_64)
            .withAnimated(1, 0)
            .withLocation(12, GBA_SCREEN_HEIGHT / 2)
            .buildPtr();

    TextStream::instance().setText("PRESS START", 14, 9);
    bg = std::unique_ptr<Background>(
            new Background(1, startscreenTiles, sizeof(startscreenTiles), startscreenMap, sizeof(startscreenMap)));
    bg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            engine->transitionIntoScene(new FightingScene(engine), new FadeOutScene(2));
        }
    }
}
