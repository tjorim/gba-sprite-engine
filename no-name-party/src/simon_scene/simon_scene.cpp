//
// Created by tiele on 18/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "simon_scene.h"

SimonScene::SimonScene(const std::shared_ptr <GBAEngine> &engine, Character character) : Scene(engine),
                                                                                       character(character) {}

std::vector<Background *> SimonScene::backgrounds() {
    return {
            //background_tiles.get()
    };
}

std::vector<Sprite *> SimonScene::sprites() {
    std::vector < Sprite * > sprites;

    for (auto &colour : colours) {
        sprites.push_back(colour.get());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void SimonScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
        new BackgroundPaletteManager());
            //new BackgroundPaletteManager(background_tilesPal, sizeof(background_tilesPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
        new ForegroundPaletteManager());
            //new ForegroundPaletteManager(shared_race_scenePal, sizeof(shared_race_scenePal)));

    /*background_tiles = std::unique_ptr<Background>(
            new Background(1, background_tilesTiles, sizeof(background_tilesTiles),
                           background_tilesMap, sizeof(background_tilesMap)));
    background_tiles->useMapScreenBlock(16);*/
}

void SimonScene::tick(u16 keys) {
    TextStream::instance().setFontColor(PaletteManager::color(31, 31, 31));

    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        //startPlaying();
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //stopPlaying();
    }

    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
    }

    TextStream::instance().setText(std::string("Simon scene"), 0, 0);
}