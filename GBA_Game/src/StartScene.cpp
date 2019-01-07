//
// Created by Wout Briels on 3/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "BG_data.h"
#include "StartScene.h"
#include "Level2Scene.h"
#include "MetaData.h"


int health;
int level;

std::vector<Background *> StartScene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return{};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette));

    TextStream::instance().setText("Welcome!", 9, 10);
    TextStream::instance().setText("Press Start.", 11, 9);

    health = 3;
    level = 2;

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map_start, sizeof(map_start)));
    bg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {
    bgY += 0.5;
    bg->scroll(0, bgY);

    if (keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }
}