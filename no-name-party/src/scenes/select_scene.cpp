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
    if (keys & KEY_A) {
        engine->setScene(new GameScene(engine/*, getLevel()*/));
    } else if (keys & KEY_LEFT) {
        characterLeft();
    } else if (keys & KEY_RIGHT) {
        characterRight();
    }

    TextStream::instance().setText(std::string("Start scene"), 5, 1);
    TextStream::instance().setText(std::string("Character: ") + std::to_string(character), 10, 1);
}

int SelectScene::getCharacter() const {
    return character;
}

void SelectScene::setCharacter(int character) {
    SelectScene::character = character;
}

void SelectScene::characterLeft() {
    if (character > 1) {
        character--;
    } else {
        setCharacter(1);
    }
}

void SelectScene::characterRight() {
    if (character < 4) {
        character++;
    } else {
        setCharacter(4);
    }
}
