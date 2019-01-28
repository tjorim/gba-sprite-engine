//
// Created by JT
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "end_scene.h"
#include "../sound.h"

std::vector<Background *> EndScene::backgrounds() {
    return {};
}

std::vector<Sprite *> EndScene::sprites() {
    return {};
}

void EndScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    //engine->getTimer()->start();
    engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
    TextStream::instance().setText(std::string("End scene"), 5, 1);
    TextStream::instance().setText(std::string("Je bent dood!"), 10, 1);
}

void EndScene::tick(u16 keys) {
 }