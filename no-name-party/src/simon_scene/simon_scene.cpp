//
// Created by tiele on 18/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "simon_scene.h"

#include "foreground/sprites/shared_simon_scene.h"

#include "foreground/sprites/simon_blue.h"
#include "foreground/sprites/simon_green.h"
#include "foreground/sprites/simon_red.h"
#include "foreground/sprites/simon_yellow.h"

SimonScene::SimonScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player) : Scene(engine),
                                                                                       player(player) {}

std::vector<Background *> SimonScene::backgrounds() {
    return {};
}

std::vector<Sprite *> SimonScene::sprites() {
    std::vector < Sprite * > sprites;

    for (auto &colour : colours) {
        sprites.push_back(colour.get());
    }

    return sprites;
}

void SimonScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_simon_scenePal, sizeof(shared_simon_scenePal)));

    engine->getTimer()->start();

    createColours();
    generateSequence();
}

void SimonScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        //startPlaying();
        showSeqColours();
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //stopPlaying();
        score++;
    }

    // red
    down_last = down_now;
    if (keys & KEY_DOWN) {
        down_now = true;
        input_colours[2] = true;
    } else {
        down_now = false;
        input_colours[2] = false;
    }
    if (down_now == true && down_last == false) {
    }

    // blue
    up_last = up_now;
    if (keys & KEY_UP) {
        up_now = true;
        input_colours[0] = true;
    } else {
        up_now = false;
        input_colours[0] = false;
    }
    if (up_now == true && up_last == false) {
    }

    // yellow
    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
        input_colours[3] = true;
    } else {
        left_now = false;
        input_colours[3] = false;
    }
    if (left_now == true && left_last == false) {
    }

    // green
    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
        input_colours[1] = true;
    } else {
        right_now = false;
        input_colours[1] = false;
    }
    if (right_now == true && right_last == false) {
    }

    updateColours();

    TextStream::instance().setText(std::string("Simon scene"), 0, 0);
}

void SimonScene::createColours() {
    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    blue_colour = spriteBuilder->withData(simon_blueTiles, sizeof(simon_blueTiles))
            .withSize(SIZE_64_64)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 4 - 32)
            .buildPtr();

    green_colour = spriteBuilder->withData(simon_greenTiles, sizeof(simon_greenTiles))
            .withSize(SIZE_64_64)
            .withLocation(3*GBA_SCREEN_WIDTH / 4 - 16, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    red_colour = spriteBuilder->withData(simon_redTiles, sizeof(simon_redTiles))
            .withSize(SIZE_64_64)
            .withLocation(GBA_SCREEN_WIDTH / 2 - 32, 3*GBA_SCREEN_HEIGHT / 4 - 32)
            .buildPtr();

    yellow_colour = spriteBuilder->withData(simon_yellowTiles, sizeof(simon_yellowTiles))
            .withSize(SIZE_64_64)
            .withLocation(GBA_SCREEN_WIDTH / 4 - 48, GBA_SCREEN_HEIGHT / 2 - 32)
            .buildPtr();

    colours.push_back(std::move(blue_colour));
    colours.push_back(std::move(green_colour));
    colours.push_back(std::move(red_colour));
    colours.push_back(std::move(yellow_colour));
}

void SimonScene::updateColours() {
    for (int i = 0; i < 4; i++) {
        if (input_colours[i] || output_colours[i]) {
            colours[i]->animateToFrame(1);
        } else {
            colours[i]->animateToFrame(0);
        }
    }
}

void SimonScene::resetOutputColours() {
    for (int i = 0; i < 4; i++) {
        output_colours[i] = false;
    }
}

/* Store 15 random numbers from 1 to 4 */
void SimonScene::generateSequence() {
    for (int i = 0; i < n; i++) {
        output_seq[i] = rand() % 4;
    }
}

/* toon kleuren van begin tot huidig level */
void SimonScene::showSeqColours() {
    for (int i = 0; i < score ; i++) {
        resetOutputColours();

        engine->getTimer()->reset();

        output_colours[output_seq[i]] = true;

        //updateColours();
        //engine->updateSpritesInScene();

        /* single thread, moet vervangen worden door een if */
        while (engine->getTimer()->getMsecs() < 600) ;

        resetOutputColours();

        //updateColours();
        //engine->updateSpritesInScene();

        /* single thread, moet vervangen worden door een if */
        while (engine->getTimer()->getMsecs() < 800) ;
    }
}

/* lees kleuren in van begin tot huidig level */
void SimonScene::getInputSeq() {
    for (int i = 0 ;i < score; i++ ) {
        /* hier checken of ingevoerde code klopt */
    }
}