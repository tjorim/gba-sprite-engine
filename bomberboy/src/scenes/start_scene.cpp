//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "../sound.h"
#include "start_scene.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> StartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> StartScene::sprites() {
    return {};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void StartScene::tick(u16 keys) {
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine, getLevel()));
    } else if ((keys & KEY_LEFT) || (keys & KEY_DOWN)) {
        levelDown();
    } else if ((keys & KEY_RIGHT) || (keys & KEY_UP)) {
        levelUp();
    }

    TextStream::instance().setText(std::string("Start scene"), 5, 1);

    TextStream::instance().setText(std::string("Level: ") + std::to_string(level), 10, 1);
}

int StartScene::getLevel() const {
    return level;
}

void StartScene::setLevel(int level) {
    StartScene::level = level;
}

void StartScene::levelUp() {
    if (level < 4) {
        level++;
    } else {
        setLevel(4);
    }
}

void StartScene::levelDown() {
    if (level > 1) {
        level--;
    } else {
        setLevel(1);
    }
}
