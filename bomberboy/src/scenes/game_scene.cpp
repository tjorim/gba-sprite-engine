//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "end_scene.h"

GameScene::GameScene(const std::shared_ptr<GBAEngine> &engine, int level) : Scene(engine), level(level) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    return {};
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    // engine->getTimer()->start();
    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));

    EndScene *endScene = new EndScene(engine);
}

void GameScene::tick(u16 keys) {
    /*
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine, getLevel()));
    } else if (keys & KEY_LEFT) {
        playerLeft();
    } else if (keys & KEY_RIGHT) {
        playerRight();
    } else if (keys & KEY_DOWN) {
        playerDown();
    } else if (keys & KEY_UP) {
        playerUp();
    }
    /*
    if(engine->getTimer()->getTotalMsecs() < 5000) {
        counter++;
    } else {
        engine->getTimer()->stop();
    }

    TextStream::instance().setText(std::to_string(counter) + std::string(" frames/5sec"), 5, 1);
    TextStream::instance().setText(std::string(engine->getTimer()->to_string()), 6, 1);
    */
}