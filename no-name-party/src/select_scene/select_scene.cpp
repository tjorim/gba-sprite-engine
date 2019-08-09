//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "select_scene.h"
#include "../game_scene/game_scene.h"
#include "../../sprites/foreground/shared.h"
#include "foreground/sprites/luigi_select.h"
#include "foreground/sprites/mario_select.h"
#include "foreground/sprites/princess_peach_select.h"
#include "foreground/sprites/yoshi_select.h"
//#include "../sound.h"

SelectScene::SelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> SelectScene::backgrounds() {
    return {};
}

std::vector<Sprite *> SelectScene::sprites() {
    std::vector<Sprite *> sprites;

    for (auto &character : characters) {
        sprites.push_back(character.get());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void SelectScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    luigi_select = spriteBuilder->withData(luigi_selectTiles, sizeof(luigi_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 97, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    mario_select = spriteBuilder->withData(mario_selectTiles, sizeof(mario_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 43, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    princess_peach_select = spriteBuilder->withData(princess_peach_selectTiles, sizeof(princess_peach_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 + 11, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    yoshi_select = spriteBuilder->withData(yoshi_selectTiles, sizeof(yoshi_selectTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 + 65, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    characters.push_back(std::move(luigi_select));
    characters.push_back(std::move(mario_select));
    characters.push_back(std::move(princess_peach_select));
    characters.push_back(std::move(yoshi_select));

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
        if (character_current % 2) {
            TextStream::instance().setText(std::string("Sorry, enkel Luigi en Princess Peach zijn beschikbaar "), 12,
                                           1);
        } else {
            engine->setScene(new GameScene(engine, getCharacter()));
        }
    }

    TextStream::instance().setText(std::string("Select scene"), 0, 0);
    TextStream::instance().setText(std::string("Character: ") + std::to_string(character_current + 1), 2, 0);
}

int SelectScene::getCharacter() const {
    return character_current;
}

void SelectScene::setCharacter(int character) {
    SelectScene::character_current = character;
    updateCharacter();
}

void SelectScene::updateCharacter() {
    unselectCharacter(character_previous);
    selectCharacter(character_current);
    character_previous = character_current;
}

void SelectScene::unselectCharacter(int character) {
    characters[character]->animateToFrame(0);
}

void SelectScene::selectCharacter(int character) {
    characters[character]->animateToFrame(1);
}

void SelectScene::characterLeft() {
    if (character_current > 0) {
        character_current--;
        updateCharacter();
    }
}

void SelectScene::characterRight() {
    if (character_current < 3) {
        character_current++;
        updateCharacter();
    }
}
