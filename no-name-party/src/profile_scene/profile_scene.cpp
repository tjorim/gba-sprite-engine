//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "../select_scene/select_scene.h"
#include "profile_scene.h"
#include "../game_scene/game_scene.h"

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
        engine->setScene(new SelectScene(engine));
    }
}

Character ProfileScene::getCharacter() const {
    return character;
}

void ProfileScene::setCharacter(const Character &value) {
    character = value;
}
