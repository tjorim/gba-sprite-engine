//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "select_scene.h"
#include "game_scene.h"
#include "../../sprites/shared.h"
#include "../../sprites/luigi_select.h"
#include "../../sprites/princess_peach_select.h"
#include "../../sprites/mario_select.h"
#include "../../sprites/yoshi_select.h"
//#include "../sound.h"

SelectScene::SelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> SelectScene::backgrounds() {
    return {};
}

std::vector<Sprite *> SelectScene::sprites() {
    std::vector < Sprite * > sprites;

    for (auto& character : characters) {
        sprites.push_back(character.get());
    }

    return sprites;
}

void SelectScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
        new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    characters.push_back(
        spriteBuilder->withData(Luigi_selectTiles, sizeof(Luigi_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 97, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr()
    );

    characters.push_back(
        spriteBuilder->withData(Princess_Peach_selectTiles, sizeof(Princess_Peach_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 43, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr()
    );

    characters.push_back(
        spriteBuilder->withData(Mario_selectTiles, sizeof(Mario_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 + 11, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr()
    );

    characters.push_back(
        spriteBuilder->withData(Yoshi_selectTiles, sizeof(Yoshi_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 + 65, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr()
    );

    updateCharacter();

    //engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void SelectScene::tick(u16 keys) {
    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
        characterLeft();
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
        characterRight();
    }
    
    if (keys & KEY_A) {
        engine->setScene(new GameScene(engine/*, getLevel()*/));
    }

    TextStream::instance().setText(std::string("Select scene"), 5, 1);
    TextStream::instance().setText(std::string("Character: ") + std::to_string(character), 10, 1);
}

int SelectScene::getCharacter() const {
    return character;
}

void SelectScene::setCharacter(int character) {
    SelectScene::character = character;
    updateCharacter();
}

void SelectScene::updateCharacter() {
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
