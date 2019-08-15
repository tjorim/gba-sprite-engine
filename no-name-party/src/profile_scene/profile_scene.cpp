//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "../select_scene/select_scene.h"
#include "profile_scene.h"
#include "../game_scene/game_scene.h"
#include "../book_scene/book_scene.h"
#include "../dino_scene/dino_scene.h"
#include "../race_scene/race_scene.h"

#include "sound_04_view_passport.h"
#include "background/background_profile.h"

ProfileScene::ProfileScene(const std::shared_ptr<GBAEngine> &engine, Character character) : Scene(engine), character(character) {}

std::vector<Background *> ProfileScene::backgrounds() {
    return {
        background_profile.get()
    };
}

std::vector<Sprite *> ProfileScene::sprites() {
    return {};
}

void ProfileScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_profilePal, sizeof(background_profilePal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager());

    background_profile = std::unique_ptr<Background>(
            new Background(1, background_profileTiles, sizeof(background_profileTiles),
                           background_profileMap, sizeof(background_profileMap)));
    background_profile->useMapScreenBlock(16);

    engine->enqueueMusic(sound_04_view_passport, sizeof(sound_04_view_passport));
}

void ProfileScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        engine->setScene(new GameScene(engine, getCharacter()));
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //engine->setScene(new SelectScene(engine));
    }

    down_last = down_now;
    if (keys & KEY_DOWN) {
        down_now = true;
    } else {
        down_now = false;
    }
    if (down_now == true && down_last == false) {
        engine->setScene(new BookScene(engine, getCharacter()));
    }

    up_last = up_now;
    if (keys & KEY_UP) {
        up_now = true;
    } else {
        up_now = false;
    }
    if (up_now == true && up_last == false) {
        engine->setScene(new DinoScene(engine, getCharacter()));
    }

    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
        engine->setScene(new RaceScene(engine, getCharacter()));
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
        //engine->setScene(new PlantScene(engine, getCharacter()));
    }

    TextStream::instance().setText(std::string("Profile scene"), 0, 0);
    TextStream::instance().setFontColor(PaletteManager::color(0, 0, 0));
    TextStream::instance().setText(std::string("Down = book"), 4, 14);
    TextStream::instance().setText(std::string("Up   = dino"), 8, 14);
    TextStream::instance().setText(std::string("Left = race"), 12, 14);
    //TextStream::instance().setText(std::string("Right = plants"), 16, 6);
}

Character ProfileScene::getCharacter() const {
    return character;
}

void ProfileScene::setCharacter(const Character &value) {
    character = value;
}
