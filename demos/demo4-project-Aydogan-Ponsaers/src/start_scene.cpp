//
// Created by aydoganmusa on 21.11.18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "roshi.h"
#include "start_scene.h"
#include "fighting_scene.h"


std::vector<Background *> StartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> StartScene::sprites() {
    return {  animation.get() };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(roshi_palette, sizeof(roshi_palette)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    animation = builder
            .withData(roshi_data, sizeof(roshi_data))
            .withSize(SIZE_32_64)
            .withAnimated(1, 0)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    TextStream::instance().setText("PRESS START", 3, 10);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            engine->transitionIntoScene(new FightingScene(engine), new FadeOutScene(2));
        }
    }
}
