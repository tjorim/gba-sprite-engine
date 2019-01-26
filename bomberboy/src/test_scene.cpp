//
// Created by JT
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "test_scene.h"
#include "sound.h"

std::vector<Background *> TestScene::backgrounds() {
    return {};
}

std::vector<Sprite *> TestScene::sprites() {
    return {};
}

void TestScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    engine->getTimer()->start();
    engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void TestScene::tick(u16 keys) {
    if(engine->getTimer()->getTotalMsecs() < 5000) {
        counter++;
    } else {
        engine->getTimer()->stop();
    }

    TextStream::instance().setText(std::to_string(counter) + std::string(" frames/5sec"), 5, 1);
    TextStream::instance().setText(std::string(engine->getTimer()->to_string()), 6, 1);
 }