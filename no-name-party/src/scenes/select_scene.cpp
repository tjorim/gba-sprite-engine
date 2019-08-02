//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "select_scene.h"
#include "game_scene.h"
#include "../../sprites/shared.h"
//#include "../sound.h"

SelectScene::SelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> SelectScene::backgrounds() {
    return {};
}

std::vector<Sprite *> SelectScene::sprites() {
    return {};
}

void SelectScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
        new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    //engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void SelectScene::tick(u16 keys) {
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine/*, getLevel()*/));
    } else if ((keys & KEY_LEFT) || (keys & KEY_DOWN)) {
        levelDown();
    } else if ((keys & KEY_RIGHT) || (keys & KEY_UP)) {
        levelUp();
    }

    TextStream::instance().setText(std::string("Start scene"), 5, 1);
    TextStream::instance().setText(std::string("Level: ") + std::to_string(level), 10, 1);
}

int SelectScene::getLevel() const {
    return level;
}

void SelectScene::setLevel(int level) {
    SelectScene::level = level;
}

void SelectScene::levelUp() {
    if (level < 4) {
        level++;
    } else {
        setLevel(4);
    }
}

void SelectScene::levelDown() {
    if (level > 1) {
        level--;
    } else {
        setLevel(1);
    }
}
