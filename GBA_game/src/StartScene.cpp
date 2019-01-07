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
#include "linkAnimation.h"
#include "levelSound.h"
#include "Direction.h"
#include "shared.h"
#include "sign.h"
#include "mapMatrix.h"

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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal1, sizeof(sharedPal1)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(IntroBGPal, sizeof(IntroBGPal)));

    SpriteBuilder<Sprite> builder;


    sign = builder
            .withData(SignTiles, sizeof(SignTiles))
            .withSize(SIZE_16_16)
            .withLocation(155, 30)
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
    //int currentXTile;
    //int currentYTile;


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

        } else if (keys & KEY_RIGHT) {
            currentDir = Direction::RIGHT;
            linkAnimation->flipHorizontally(true);
            if (playerX <= GBA_SCREEN_WIDTH - linkAnimation.get()->getWidth()) {
                if (isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir)) {
                    playerX++;
                    linkAnimation->makeAnimated(4, 5, 12);
                }
            }

        } else if (keys & KEY_UP) {
            currentDir = Direction::UP;
            if (playerY > 1) {
                if (isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir)) {
                    playerY--;
                    //linkAnimation->stopAnimating();
                    linkAnimation->makeAnimated(6, 5, 0);
                }
            }
        } else if (keys & KEY_LEFT) {
            currentDir = Direction::LEFT;
            linkAnimation->flipHorizontally(false);
            if (playerX > 1) {
                if (isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir)) {
                    playerX--;
                    linkAnimation->makeAnimated(4, 5, 12);
                }
            }
        } else if (keys & KEY_DOWN) {
            currentDir = Direction::DOWN;
            if (playerY <= GBA_SCREEN_HEIGHT - linkAnimation.get()->getHeight()) {
                if (isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir)) {
                    playerY++;
                    linkAnimation->makeAnimated(6, 5, 6);
                }
            }
        }  else if (!keys) {
            if (currentDir == Direction::UP){
                linkAnimation->animateToFrame(0);
            } else if (currentDir == Direction::DOWN){
                linkAnimation->animateToFrame(6);
            } else if (currentDir == Direction::LEFT || currentDir == Direction::RIGHT){
            linkAnimation->animateToFrame(15);
            }
            linkAnimation->stopAnimating();
        }

        if (linkAnimation->collidesWith(*sign)){
            TextStream::instance().setText("Welcome to", 15, 10);
            TextStream::instance().setText("Jonasgold", 17, 10);
            isText = true;
        } else if (isText) {
            isText = false;
            TextStream::instance().clear();
        }
        //TextStream::instance()<< bool (isNextTileGo(playerX,playerY,scrollX,scrollY));
        TextStream::instance().setText(std::to_string(isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir)), 3, 3 );

        int centerX = (playerX + 16 + scrollX);
        int centerY = (playerY + 16 + scrollY);

        int restX = (centerX) % 16;
        int restY = (centerY) % 16;

        int volgendeX = 0;
        int volgendeY = 0;

        linkAnimation->moveTo(playerX, playerY);
        sign->moveTo(160,128-scrollY);

        switch (currentDir) {
            case Direction::LEFT : {
                if (restX == 0 || restX == 1){
                    volgendeX = (centerX/16)-1;
                    volgendeY = centerY/16;
                }
                break;
            }
            case Direction::RIGHT : {
                if (restX == 14 || restX == 15){
                    volgendeX = ((centerX + 16)/16);
                    volgendeY = centerY/16;
                }
                break;
            }
            case Direction::UP : {
                if (restY == 0 || restY == 1){
                    volgendeY = (centerY - 16)/16;
                    volgendeX = centerX/16;
                }
                break;
            }
            case Direction::DOWN : {
                if (restY == 14 || restY == 15){
                    volgendeY = (centerY + 16)/16;
                    volgendeX = centerX/16;
                }
                break;
            }
        }




        TextStream::instance().setText(std::to_string(volgendeX), 7, 3 );
        TextStream::instance().setText(std::to_string(volgendeY), 6, 3);
        TextStream::instance().setText(std::to_string(centerX), 4, 3 );
        TextStream::instance().setText(std::to_string(centerY), 5, 3 );

    }
}

bool StartScene::isNextTileGo(int playerX, int playerY, int scrollX, int scrollY, Direction currentDir) {
    int centerX;
    int centerY;
    int restX;
    int restY;
    int volgendeX = 0;
    int volgendeY = 0;
    int checkX;
    int checkY;

    centerX = (playerX + 16 + scrollX);
    centerY = (playerY + 16 + scrollY);

    restX = (centerX) % 16;
    restY = (centerY) % 16;


    switch (currentDir) {
        case Direction::LEFT : {
            checkX = centerX - 7;
            restX = (checkX) % 16;
            if (restX == 0 || restX == 1){
                volgendeX = (centerX - 16)/16;
                volgendeY = centerY/16;
            }
            break;
        }
        case Direction::RIGHT : {
            checkX = centerX + 7;
            restX = (checkX) % 16;
            if (restX == 14 || restX == 15){
                volgendeX = ((centerX + 16)/16);
                volgendeY = centerY/16;
            }
            break;
        }
        case Direction::UP : {
            checkY = centerY - 4;
            restY = (checkY) % 16;
            if (restY == 0 || restY == 1){
                volgendeY = (centerY - 16)/16;
                volgendeX = centerX/16;
            }
            break;
        }
        case Direction::DOWN : {
            checkY = centerY + 4;
            restY = (checkY) % 16;
            if (restY == 14 || restY == 15){
                volgendeY = (centerY + 16)/16;
                volgendeX = centerX/16;
            }
            break;
        }
    }
    if (level1[volgendeY][volgendeX] == Type::NOGO) {
        return false;
    }
    return true;
}