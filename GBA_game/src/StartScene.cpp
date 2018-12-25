//
// Created by lloyd on 29-Nov-18.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "StartScene.h"
#include "background.h"
#include "linkUpWalk.h"
#include "linkWalkSide.h"
#include "linkDownWalk.h"
#include "levelSound.h"

std::vector<Background *> StartScene::backgrounds() {
    return{
        bg.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return {
        walkDownAnimation.get()
    };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(linkDownWalkPal, sizeof(linkDownWalkPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(IntroBGPal, sizeof(IntroBGPal)));

    SpriteBuilder<Sprite> builder;

    /*
    walkSideAnimation = builder
            .withData(LinkSideWalkTiles, sizeof(LinkSideWalkTiles))
            .withSize(SIZE_32_32)
            .withAnimated(4, 7)
            .withLocation(100, 100)
            .buildPtr();
    */

    walkDownAnimation = builder
            .withData(linkDownWalkTiles, sizeof(linkDownWalkTiles))
            .withSize(SIZE_32_32)
            .withAnimated(4, 7)
            .withLocation(100, 100)
            .buildPtr();

    playerX = 110;
    playerY = GBA_SCREEN_HEIGHT;
    scrollY = 95;
    bg->scroll(0,scrollY);


    TextStream::instance().setText("Welcome to", 5, 2);
    TextStream::instance().setText("Jonasgold", 7, 2);
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);

    bg = std::unique_ptr<Background>(new Background(1, IntroBGTiles, sizeof(IntroBGTiles), Intro_Map, sizeof(Intro_Map)));
    bg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {

    if(!walkDownAnimation.get()->isOffScreen()) {
        if (playerY < 32) {
            if (scrollY > 0) {
                scrollY = scrollY - 1;
                bg->scroll(0, scrollY);
                playerY = 32;
            }

        }

        if (playerY > 110) {
            if (scrollY < 96) {
                scrollY = scrollY + 1;
                bg->scroll(0, scrollY);
                playerY = 110;
            }
        }


        if (keys & KEY_START) {
            if (!engine->isTransitioning()) {

                engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);
                //TextStream::instance() << "entered: starting next scene";
                //engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));

            }
        } else if (keys & KEY_LEFT) {
            if (playerX > 1) {
                playerX--;
                walkDownAnimation->flipHorizontally(false);
            }

        } else if (keys & KEY_RIGHT) {
            if (playerX <= GBA_SCREEN_WIDTH - walkDownAnimation.get()->getWidth()) {
                playerX++;
                walkDownAnimation->flipHorizontally(true);
            }
        } else if (keys & KEY_UP) {
            if (playerY > 1) {
                playerY--;
                walkDownAnimation->flipVertically(false);
            }
        } else if (keys & KEY_DOWN) {
            if (playerY <= GBA_SCREEN_HEIGHT - walkDownAnimation.get()->getHeight()) {
                playerY++;
                walkDownAnimation->flipVertically(false);
            }
        }
        walkDownAnimation->moveTo(playerX, playerY);
    }
}
