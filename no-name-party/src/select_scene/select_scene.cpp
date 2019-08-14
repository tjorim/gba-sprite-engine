//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "../start_scene/start_scene.h"
#include "select_scene.h"
#include "../profile_scene/profile_scene.h"

#include "../enums/character.h"

#include "sound_03_passport_setup.h"
#include "background/background_rainbow.h"
#include "foreground/sprites/shared_select_scene.h"

#include "foreground/sprites/luigi_select.h"
#include "foreground/sprites/mario_select.h"
#include "foreground/sprites/princess_peach_select.h"
#include "foreground/sprites/yoshi_select.h"

SelectScene::SelectScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> SelectScene::backgrounds() {
    return {
            background_rainbow.get()
    };
}

std::vector<Sprite *> SelectScene::sprites() {
    std::vector<Sprite *> sprites;

    for (auto &character : characters) {
        sprites.push_back(character.get());
    }

    return sprites;
}

void SelectScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_rainbowPal, sizeof(background_rainbowPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_select_scenePal, sizeof(shared_select_scenePal)));

    background_rainbow = std::unique_ptr<Background>(
            new Background(1, background_rainbowTiles, sizeof(background_rainbowTiles),
                           background_rainbowMap, sizeof(background_rainbowMap)));
    background_rainbow->useMapScreenBlock(16);

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

    engine->enqueueMusic(sound_03_passport_setup, sizeof(sound_03_passport_setup));
}

void SelectScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        if (character_current != 1) {
            engine->setScene(new ProfileScene(engine, static_cast<Character>(getCharacter())));
        } else {
            TextStream::instance().setText(std::string("Mario is niet beschikbaar"),
                                           16, 2);
        }
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //engine->setScene(new StartScene(engine));
    }

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

    TextStream::instance().setText(std::string("Select scene"), 0, 0);
    TextStream::instance().setText(std::string("Character ") + std::to_string(character_current + 1), 0, 18);
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
