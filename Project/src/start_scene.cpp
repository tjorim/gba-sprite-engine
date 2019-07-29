//
// Created by Brecht on 29/11/2018.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "start_scene.h"
#include "game_scene.h"

std::vector<Background *> StartScene::backgrounds() {
    return {
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return {  };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().scroll(-72,-76);
    TextStream::instance() << "Lunar lander";
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            engine->transitionIntoScene(new GameScene(engine), new FadeOutScene(1000));
        }
    } else if(keys & KEY_LEFT) {

    } else if(keys & KEY_RIGHT) {

    } else if(keys & KEY_UP) {

    } else if(keys & KEY_DOWN) {

    }
    TextStream::instance().setFontColor(0x03FF);
}
