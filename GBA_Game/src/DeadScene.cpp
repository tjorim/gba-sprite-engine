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
#include "MetaData.h"


std::vector<Background *> DeadScene::backgrounds() {
    return {};
}

std::vector<Sprite *> DeadScene::sprites() {
    return{};
}

void DeadScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("You died!", 9, 10);
    TextStream::instance().setText("Press Start to restart.", 11, 5);

    health--;
}

void DeadScene::tick(u16 keys) {
    if (level == 1 && keys & KEY_START) {
        engine->transitionIntoScene(new Level1Scene(engine), new FadeOutScene(2));
    } else if (level == 2 && keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }

    // For debugging purposes!!
    if (keys & KEY_A) {     // Key X
        TextStream::instance() << level;
    } else if (keys & KEY_R) {      // Key S
        TextStream::instance().clear();
    }
}