//
// Created by Wout Briels on 3/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "StartScene.h"
#include "Level2Scene.h"
#include "MetaData.h"


int health;
int level;

std::vector<Background *> StartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> StartScene::sprites() {
    return{};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("Welcome!", 9, 10);
    TextStream::instance().setText("Press Start.", 11, 9);

    health = 3;
    level = 2;
}

void StartScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }

    // For debugging purposes!!
    if (keys & KEY_A) {     // Key X
        TextStream::instance() << "";
    } else if (keys & KEY_R) {      // Key S
        TextStream::instance().clear();
    }
}