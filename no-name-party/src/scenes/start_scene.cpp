//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "start_scene.h"
#include "game_scene.h"
//#include "../sound.h"
#include "../../sprites/background_rainbow.h"
#include "../../sprites/balloon_blue.h"
#include "../../sprites/balloon_green.h"
#include "../../sprites/balloon_pink.h"
#include "../../sprites/balloon_yellow.h"
#include "../../sprites/press_start_left.h"
#include "../../sprites/press_start_right.h"
#include "../../sprites/shared.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> StartScene::backgrounds() {
    return {
        //bg_map.get()
        };
}

std::vector<Sprite *> StartScene::sprites() {
    std::vector < Sprite * > sprites;

    sprites.push_back(balloon_blue.get());
    sprites.push_back(balloon_green.get());
    sprites.push_back(balloon_pink.get());
    sprites.push_back(balloon_yellow.get());

    for (auto& balloon : balloons) {
        sprites.push_back(balloon->getSprite());
    }

    sprites.push_back(press_start_left.get());
    sprites.push_back(press_start_right.get());

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 12, 1);
    return sprites;
}

void StartScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
        new BackgroundPaletteManager(background_rainbowPal, sizeof(background_rainbowPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
        new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    bg_map = std::unique_ptr<Background>(
        new Background(1, background_rainbowTiles, sizeof(background_rainbowTiles), background_rainbowMap, sizeof(background_rainbowMap)));
    bg_map->useMapScreenBlock(16);

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    press_start_left = spriteBuilder->withData(press_start_leftTiles, sizeof(press_start_leftTiles))
            .withSize(SIZE_64_32)
            .withAnimated(22, 2)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    press_start_right = spriteBuilder->withData(press_start_rightTiles, sizeof(press_start_rightTiles))
            .withSize(SIZE_64_32)
            .withAnimated(22, 2)
            .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    balloon_blue = spriteBuilder->withData(balloon_blueTiles, sizeof(balloon_blueTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    balloon_green = spriteBuilder->withData(balloon_greenTiles, sizeof(balloon_greenTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    balloon_pink = spriteBuilder->withData(balloon_pinkTiles, sizeof(balloon_pinkTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    balloon_yellow = spriteBuilder->withData(balloon_yellowTiles, sizeof(balloon_yellowTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

        balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(spriteBuilder
            ->withLocation(10, 20)
            .buildWithDataOf(*balloon_blue.get())))
        );
        balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(spriteBuilder
            ->withLocation(20, 40)
            .buildWithDataOf(*balloon_green.get())))
        );

    TextStream::instance().setText(std::string("Start scene"), 5, 1);

    TextStream::instance().setText(std::string("Level: ") + std::to_string(level), 10, 1);
}

int StartScene::getLevel() const {

void StartScene::setLevel(int level) {
}

void StartScene::levelUp() {
    if (level < 4) {
        level++;
    } else {
        setLevel(4);
    }
}

void StartScene::levelDown() {
    if (level > 1) {
        level--;
    } else {
        setLevel(1);
    }
}
