//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../game_scene/game_scene.h"
#include "race_scene.h"

#include "background/background_tiles.h"
#include "foreground/sprites/shared_race_scene.h"
#include "foreground/sprites/walking_bomb.h"
#include "foreground/sprites/mushroom.h"

RaceScene::RaceScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player) : Scene(engine),
                                                                                       player(player) {}

std::vector<Background *> RaceScene::backgrounds() {
    return {
            background_tiles.get()
    };
}

std::vector<Sprite *> RaceScene::sprites() {
    std::vector < Sprite * > sprites;

    sprites.push_back(car->getCarSprite());

    for (auto &bomb : bombs) {
        sprites.push_back(bomb.get());
    }

    for (auto &mushroom : mushrooms) {
        sprites.push_back(mushroom.get());
    }

    if (ended) {
        sprites.push_back(game_result->getSprite());
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

    car = std::unique_ptr<Car>(new Car());
}

void RaceScene::tick(u16 keys) {
    if (playing) {
        checkCollision();

        yCo--;
        if (yCo % 2 == 0) {
            background_tiles->scroll(0, yCo / 2);
        }

        if (keys & KEY_LEFT) {
            car->getCarSprite()->setVelocity(-2, 0);
        } else if (keys & KEY_RIGHT) {
            car->getCarSprite()->setVelocity(2, 0);
        } else {
            car->getCarSprite()->setVelocity(0, 0);
        }
    } else {
        car->getCarSprite()->setVelocity(0, 0);
    }

    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        if (ended) {
            engine->setScene(new GameScene(engine, player, game_result->getResult()));
        } else {
            startPlaying();
        }
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

    TextStream::instance().setFontColor(PaletteManager::color(31, 31, 31));
    TextStream::instance().setText(std::string("Race scene"), 0, 0);
    TextStream::instance().setText(std::string(""), 4, 14);
    TextStream::instance().setText(std::string(""), 8, 14);
    TextStream::instance().setText(std::string(""), 12, 14);
    TextStream::instance().setText(std::string(""), 16, 6);
    TextStream::instance().setText(engine->getTimer()->to_string(), 18, 0);
}

void RaceScene::startPlaying() {
    placeBombs();
    giveLives();
    ended = false;
    engine->updateSpritesInScene();
    engine->getTimer()->start();

    lives = mushrooms.size();
    playing = true;
    car->getCarSprite()->animate();

    for (auto &bomb : bombs) {
        bomb->setVelocity(0, 1);
        bomb->animate();
    }
}

void RaceScene::stopPlaying() {
    bombs.clear();
    mushrooms.clear();
    engine->updateSpritesInScene();
    engine->getTimer()->stop();
    engine->getTimer()->reset();

    playing = false;
    car->getCarSprite()->stopAnimating();
    car->getCarSprite()->animateToFrame(0);

    for (auto &bomb : bombs) {
        bomb->setVelocity(0, 0);
        bomb->stopAnimating();
        bomb->animateToFrame(0);
    }
}

void RaceScene::checkCollision() {
    if (engine->getTimer()->getSecs() > 29) {
        endGame(Result::WIN);
    }

    hit_last = hit_now;
    int collisions = 0;

    for (auto &bomb : bombs) {
        if (bomb->collidesWith(*car->getCarSprite())) {
            collisions++;
        }
    }

    if (collisions > 0) {
        hit_now = true;
    } else {
        hit_now = false;
    }
    if (hit_now == true && hit_last == false) {
        takeLife();
    }
}

Character RaceScene::getCharacter() const {
    return character;
}

void RaceScene::setCharacter(const Character &value) {
    character = value;
}

void RaceScene::placeBombs() {
    SpriteBuilder <Sprite> builder;

    bombs.push_back(
            builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(0.5 * (GBA_SCREEN_WIDTH / 4), 0)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
            builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(1.5 * (GBA_SCREEN_WIDTH / 4), 64)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
            builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(2.5 * (GBA_SCREEN_WIDTH / 4), 128)
                    .withAnimated(4, 6)
                    .buildPtr()
    );

    bombs.push_back(
            builder.withData(walking_bombTiles, sizeof(walking_bombTiles))
                    .withSize(SIZE_16_32)
                    .withLocation(3.5 * (GBA_SCREEN_WIDTH / 4), 192)
                    .withAnimated(4, 6)
                    .buildPtr()
    );
}

void RaceScene::giveLives() {
    SpriteBuilder <Sprite> builder;

    mushrooms.push_back(
            builder.withData(mushroomTiles, sizeof(mushroomTiles))
                    .withSize(SIZE_16_16)
                    .withLocation(GBA_SCREEN_WIDTH - 32, 8)
                    .buildPtr()
    );

    mushrooms.push_back(
            builder.withData(mushroomTiles, sizeof(mushroomTiles))
                    .withSize(SIZE_16_16)
                    .withLocation(GBA_SCREEN_WIDTH - 32, 32)
                    .buildPtr()
    );

    mushrooms.push_back(
            builder.withData(mushroomTiles, sizeof(mushroomTiles))
                    .withSize(SIZE_16_16)
                    .withLocation(GBA_SCREEN_WIDTH - 32, 56)
                    .buildPtr()
    );
}

int RaceScene::getLives() {
    return lives;
}

void RaceScene::takeLife() {
    if (lives > 1) {
        lives--;
        mushrooms[lives]->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT);
    } else {
        endGame(Result::LOSE);
    }
}

void RaceScene::endGame(Result result) {
    stopPlaying();
    ended = true;
    game_result = std::unique_ptr<GameResult>(new GameResult(getCharacter(), result));
    engine->updateSpritesInScene();
}