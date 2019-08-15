//
// Created by tiele on 15/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>

#include "dino_scene.h"

#include "background/background_clouds.h"
#include "foreground/sprites/shared_dino_scene.h"
#include "foreground/sprites/plant.h"

DinoScene::DinoScene(const std::shared_ptr<GBAEngine> &engine, Character character) : Scene(engine), character(character) {}

std::vector<Background *> DinoScene::backgrounds() {
    return {
            background_clouds.get()
    };
}

std::vector<Sprite *> DinoScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(dino->getDinoSprite());

    for (auto &plant : plants) {
        sprites.push_back(plant.get());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void DinoScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_cloudsPal, sizeof(background_cloudsPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_dino_scenePal, sizeof(shared_dino_scenePal)));

    background_clouds = std::unique_ptr<Background>(
            new Background(1, background_cloudsTiles, sizeof(background_cloudsTiles),
                           background_cloudsMap, sizeof(background_cloudsMap)));
    background_clouds->useMapScreenBlock(16);

    placePlants();

    dino = std::unique_ptr<Dino>(new Dino());
}

void DinoScene::tick(u16 keys) {
    xCo++;
    background_clouds->scroll(xCo, 0);

    fire_last = fire_now;
    if (keys & KEY_FIRE) {
        fire_now = true;
    } else {
        fire_now = false;
    }
    if (fire_now == true && fire_last == false) {
        jump();
        //engine->setScene(new GameScene(engine, getCharacter()));
    }

    TextStream::instance().setText(std::string("Book scene"), 0, 0);
}

void DinoScene::jump() {
}

Character DinoScene::getCharacter() const {
    return character;
}

void DinoScene::setCharacter(const Character &value) {
    character = value;
}

void DinoScene::placePlants() {
    /*plants.push_back(
            std::unique_ptr<Sprite>(new Sprite())
    );*/
}