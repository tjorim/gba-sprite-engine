//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "race_scene.h"

#include "background/background_tiles.h"
#include "foreground/sprites/shared_race_scene.h"
#include "foreground/sprites/walking_bomb.h"

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
    TextStream::instance().setFontColor(PaletteManager::color(31, 31, 31));

    if (playing) {
        yCo--;
        background_tiles->scroll(0, yCo);
    }

    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        startPlaying();
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        stopPlaying();
    }

    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
        goLeft();
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
        goRight();
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
    }

    TextStream::instance().setText(std::string("Race scene"), 0, 0);
}

void RaceScene::goLeft() {
    if (xCo > 8) {
        xCo--;
        moveTo();
    }
}

void RaceScene::goRight() {
    if (xCo < GBA_SCREEN_WIDTH - 24) {
        xCo++;
        moveTo();
    }
}

void RaceScene::moveTo() {
    car->moveToX(xCo);
}

void RaceScene::startPlaying() {
    playing = true;

    for (auto &bomb : bombs) {
        bomb->setVelocity(0, 1);
        bomb->animate();
    }
}

void RaceScene::stopPlaying() {
    playing = false;

    for (auto &bomb : bombs) {
        bomb->setVelocity(0, 0);
        bomb->stopAnimating();
        bomb->animateToFrame(0);
    }
}

Character RaceScene::getCharacter() const {
    return character;
}

void RaceScene::setCharacter(const Character &value) {
    character = value;
}

void RaceScene::placeBombs() {
    SpriteBuilder<Sprite> builder;

    bombs.push_back(
        builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(0.5*(GBA_SCREEN_WIDTH/4), 0)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
        builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(1.5*(GBA_SCREEN_WIDTH/4), 64)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
        builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(2.5*(GBA_SCREEN_WIDTH/4), 128)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
        builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(3.5*(GBA_SCREEN_WIDTH/4), 192)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    stopPlaying();
}