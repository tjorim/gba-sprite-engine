//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>

#include "race_scene.h"

#include "background/background_tiles.h"
#include "foreground/sprites/shared_race_scene.h"

RaceScene::RaceScene(const std::shared_ptr<GBAEngine> &engine, Character character) : Scene(engine), character(character) {}

std::vector<Background *> RaceScene::backgrounds() {
    return {
            background_tiles.get()
    };
}

std::vector<Sprite *> RaceScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(car->getCarSprite());

    for (auto &bomb : bombs) {
        sprites.push_back(bomb.get());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void RaceScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_tilesPal, sizeof(background_tilesPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_race_scenePal, sizeof(shared_race_scenePal)));

    background_tiles = std::unique_ptr<Background>(
            new Background(1, background_tilesTiles, sizeof(background_tilesTiles),
                           background_tilesMap, sizeof(background_tilesMap)));
    background_tiles->useMapScreenBlock(16);

    placeBombs();

    car = std::unique_ptr<Car>(new Car());
}

void RaceScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        //engine->setScene(new GameScene(engine, getCharacter()));
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //engine->setScene(new StartScene(engine));
        //engine->dequeueAllSounds();
        //engine->enqueueMusic(Title_Screen_wav, sizeof(Title_Screen_wav));
    }

    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
        goLeft();
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
        goRight();
    }

    TextStream::instance().setText(std::string("Book scene"), 0, 0);
}

void RaceScene::goLeft() {
    if (xCo > 0) {
        xCo--;
        moveTo();
    }
}

void RaceScene::goRight() {
    if (xCo < 240) {
        xCo++;
        moveTo();
    }
}

void RaceScene::moveTo() {
    car->moveTo(xCo);
}

Character RaceScene::getCharacter() const {
    return character;
}

void RaceScene::setCharacter(const Character &value) {
    character = value;
}

void RaceScene::placeBombs() {
    /*bombs.push_back(
            std::unique_ptr<Sprite>(new Sprite())
    );*/
}