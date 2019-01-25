//
// Created by Wout Briels on 6/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Level2Scene.h"
#include "EndScene.h"
#include "SharedData.h"


std::vector<Background *> EndScene::backgrounds() {
    return {};
}

std::vector<Sprite *> EndScene::sprites() {
    return{};
}

void EndScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("Game completed", 9, 7);
    TextStream::instance().setText("Press Start to restart.", 11, 5);

    health = 3;
}

void EndScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }
}