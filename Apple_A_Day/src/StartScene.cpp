//
// Created by lloyd on 29-Nov-18.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "StartScene.h"
#include "background1.h"
#include "levelSound.h"
#include "Direction.h"
#include "mapMatrix.h"
#include "levelControl.h"
#include "CityScene.h"
#include "apple.h"
#include "linkAnimation.h"
#include "sharedPalette.h"
#include "sign.h"
#include "windowBullet.h"
#include "enemy.h"

levelControl mControl1;

std::vector<Background *> StartScene::backgrounds() {
    return{
        bg.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return {
        linkAnimation.get(),
        sign.get()
    };
}

void StartScene::load() {

    linkAnimation->stopAnimating();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(IntroBGPal, sizeof(IntroBGPal)));

    SpriteBuilder<Sprite> builder;

    sign = builder
            .withData(SignTiles, sizeof(SignTiles))
            .withSize(SIZE_16_16)
            .withLocation(160, 28)
            .buildPtr();

    linkAnimation = builder
            .withData(linkAnimationTiles, sizeof(linkAnimationTiles))
            .withSize(SIZE_32_32)
            .withLocation(100, 100)
            .buildPtr();


    playerX = 110;
    playerY = GBA_SCREEN_HEIGHT;
    i = 0;
    isText = false;
    currentDir = Direction::UP;
    scrollY = 95;
    bg->scroll(0,scrollY);

    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);

    bg = std::unique_ptr<Background>(new Background(1, IntroBGTiles, sizeof(IntroBGTiles), Intro_Map, sizeof(Intro_Map)));
    bg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {

    if(!linkAnimation.get()->isOffScreen()) {
        if (playerY < 32) {
            if (scrollY > 0) {
                scrollY = scrollY - 1;
                bg->scroll(0, scrollY);
                playerY = 32;
            }
        } else if (playerY > 110) {
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

        } else if (keys & KEY_RIGHT) {
            currentDir = Direction::RIGHT;
            linkAnimation->flipHorizontally(true);
            isNextTileGo = mControl1.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 1);
            if (playerX <= GBA_SCREEN_WIDTH - linkAnimation.get()->getWidth()) {
                if (isNextTileGo) {
                    playerX++;
                    linkAnimation->makeAnimated(4, 5, 12);
                }
            }

        } else if (keys & KEY_UP) {
            currentDir = Direction::UP;
            isNextTileGo = mControl1.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 1);
            if (playerY > 1) {
                if (isNextTileGo) {
                    playerY--;
                    //linkAnimation->stopAnimating();
                    linkAnimation->makeAnimated(6, 5, 0);
                }
            }
        } else if (keys & KEY_LEFT) {
            currentDir = Direction::LEFT;
            linkAnimation->flipHorizontally(false);
            isNextTileGo = mControl1.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 1);
            if (playerX > 1) {
                if (isNextTileGo) {
                    playerX--;
                    linkAnimation->makeAnimated(4, 5, 12);
                }
            }
        } else if (keys & KEY_DOWN) {
            currentDir = Direction::DOWN;
            isNextTileGo = mControl1.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 1);
            if (playerY <= GBA_SCREEN_HEIGHT - linkAnimation.get()->getHeight()) {
                if (isNextTileGo) {
                    playerY++;
                    linkAnimation->makeAnimated(6, 5, 6);
                }
            }
        } else if (!keys) {
            if (currentDir == Direction::UP) {
                linkAnimation->animateToFrame(0);
            } else if (currentDir == Direction::DOWN) {
                linkAnimation->animateToFrame(6);
            } else if (currentDir == Direction::LEFT || currentDir == Direction::RIGHT) {
                linkAnimation->animateToFrame(15);
            }
            linkAnimation->stopAnimating();
        }


        if (linkAnimation->collidesWith(*sign)) {
            TextStream::instance().setText("Welcome to", 15, 10);
            TextStream::instance().setText("Jonasgold", 16, 10);
            isText = true;
        } else if (isText) {
            isText = false;
            TextStream::instance().clear();
        }

        //TextStream::instance()<< bool (isNextTileGo(playerX,playerY,scrollX,scrollY));

        linkAnimation->moveTo(playerX, playerY);
        sign->moveTo(160, 128 - scrollY);

        if (playerX > 100 && playerX < 140 && playerY < 5) {
            engine.get()->setScene(new CityScene(engine));
        }
    }
}
