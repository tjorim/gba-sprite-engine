//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "start_scene.h"
#include "select_scene.h"
//#include "../sound.h"

#include "../../sprites/background/background_rainbow.h"
#include "../../sprites/foreground/shared.h"

StartScene::StartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Background *> StartScene::backgrounds() {
    return {
            bg_map.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    std::vector<Sprite *> sprites;

    for (auto &balloon : balloons) {
        sprites.push_back(balloon->getSprite());
    }

    sprites.push_back(cloud->getSpriteLeft());
    sprites.push_back(cloud->getSpriteRight());

    sprites.push_back(press_start->getSpriteLeft());
    sprites.push_back(press_start->getSpriteRight());

    sprites.push_back(title->getSpriteLeft());
    sprites.push_back(title->getSpriteMiddle());
    sprites.push_back(title->getSpriteRight());

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void StartScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_rainbowPal, sizeof(background_rainbowPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    bg_map = std::unique_ptr<Background>(
            new Background(1, background_rainbowTiles, sizeof(background_rainbowTiles), background_rainbowMap,
                           sizeof(background_rainbowMap)));
    bg_map->useMapScreenBlock(16);

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    /*press_start_left = spriteBuilder->withData(press_start_left_singleTiles, sizeof(press_start_left_singleTiles))
            .withSize(SIZE_64_32)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    press_start_right = spriteBuilder->withData(press_start_right_singleTiles, sizeof(press_start_right_singleTiles))
            .withSize(SIZE_64_32)
            .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();*/
    cloud = std::unique_ptr<Cloud>(new Cloud(GBA_SCREEN_HEIGHT / 2, -1, 0));
    press_start = std::unique_ptr<PressStart>(new PressStart());
    title = std::unique_ptr<Title>(new Title());

    balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(Colour::BLUE, 10, -1, 0))
    );
    balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(Colour::GREEN, 50, -2, 0))
    );
    balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(Colour::PINK, 150, -1, 40))
    );
    balloons.push_back(
            std::unique_ptr<Balloon>(new Balloon(Colour::YELLOW, 200, -2, 40))
    );

    //engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void StartScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->setScene(new SelectScene(engine));
    }

    TextStream::instance().setText(std::string("Intro scene"), 0, 0);
}
