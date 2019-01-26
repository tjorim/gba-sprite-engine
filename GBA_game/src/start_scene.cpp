//
// Created by joost on 29/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "start_scene.h"
#include "background.h"
#include "backgroundtest.h"
#include "scene_level1.h"
#include "Sound.h"

std::vector<Background *> StartScene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return {};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));

    bg = std::unique_ptr<Background>(new Background(1, backgroundTiles, sizeof(backgroundTiles),
            backgroundMap, sizeof(backgroundMap)));
    engine->disableText();

    bg->useMapScreenBlock(28);
    engine->enqueueMusic(test, sizeof(test), 88200);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_ANY) {
        engine->setScene(new SceneLevel1(engine));
    }
}