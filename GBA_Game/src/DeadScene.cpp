//
// Created by Wout Briels on 3/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "DeadScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "SharedData.h"


std::vector<Background *> DeadScene::backgrounds() {
    return {};
}

std::vector<Sprite *> DeadScene::sprites() {
    return{};
}

void DeadScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    health--;
    if (health > 0) {
        TextStream::instance().setText("You died!", 9, 10);
        TextStream::instance().setText("Press Start to restart level.", 11, 1);
    } else {
        TextStream::instance().setText("No health left!", 8, 8);
        TextStream::instance().setText("Game over!!", 10, 10);
        TextStream::instance().setText("Press Start to restart game.", 12, 1);
    }
}

void DeadScene::tick(u16 keys) {
    if (health > 0 && level == 1 && keys & KEY_START) {
        engine->transitionIntoScene(new Level1Scene(engine), new FadeOutScene(2));
    } else if (health > 0 && level == 2 && keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    } else if (keys && KEY_START) {
        health = 3;
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }
}