//
// Created by lloyd on 09-Jan-19.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "CityScene.h"
#include "StartScene.h"
#include "background2.h"
#include "linkAnimation.h"
#include "levelSound.h"
#include "Direction.h"
#include "sign.h"
#include "mapMatrix.h"
#include "levelControl.h"
#include "apple.h"
#include "linkAnimation.h"
#include "sharedPalette.h"
#include "sign.h"
#include "windowBullet.h"
#include "enemy.h"


levelControl mControl2;
int cooldown;
int shootSpeed;
bool enemy1Dead, enemy2Dead; //, enemy3Dead;

std::vector<Background *> CityScene::backgrounds() {
    return{
            bg.get()
    };
}

std::vector<Sprite *> CityScene::sprites() {
    return {
        apple.get(),
        linkAnimation.get(),
        sign.get(),
        bullet1.get(),
        bullet2.get(),
        //bullet3.get(),
        enemy1.get(),
        enemy2.get()
    };
}

void CityScene::load() {

    linkAnimation->stopAnimating();

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(CityBGPal, sizeof(CityBGPal)));

    SpriteBuilder<Sprite> builder;


    sign = builder
            .withData(SignTiles, sizeof(SignTiles))
            .withSize(SIZE_16_16)
            .withLocation(100, 2)
            .buildPtr();
    sign->setStayWithinBounds(false);

    apple = builder
            .withData(appelTiles, sizeof(appelTiles))
            .withSize(SIZE_8_8)
            .withLocation(500, 50)
            .buildPtr();
    apple->setStayWithinBounds(false);

    linkAnimation = builder
            .withData(linkAnimationTiles, sizeof(linkAnimationTiles))
            .withSize(SIZE_32_32)
            .withLocation(128, 48)
            .buildPtr();

    bullet1 = builder
            .withData(window_Bullet_Tiles, sizeof(window_Bullet_Tiles))
            .withSize(SIZE_8_8)
            .withLocation(400, 1)
            .buildPtr();
    bullet1->setStayWithinBounds(false);

    bullet2 = builder
            .withData(window_Bullet_Tiles, sizeof(window_Bullet_Tiles))
            .withSize(SIZE_8_8)
            .withLocation(400, 10)
            .buildPtr();
    bullet2->setStayWithinBounds(false);

    /*
    bullet3 = builder
            .withData(window_Bullet_Tiles, sizeof(window_Bullet_Tiles))
            .withSize(SIZE_8_8)
            .withLocation(400, 20)
            .buildPtr();
    bullet3->setStayWithinBounds(false);
    */

    enemy1 = builder
            .withData(enemyTiles, sizeof(enemyTiles))
            .withSize(SIZE_16_16)
            .withLocation(enemy1X, enemy1Y)
            .buildPtr();
    enemy1->setStayWithinBounds(false);

    enemy2 = builder
            .withData(enemyTiles, sizeof(enemyTiles))
            .withSize(SIZE_16_16)
            .withLocation(enemy2X, enemy2Y)
            .buildPtr();
    enemy2->setStayWithinBounds(false);

    /*
    enemy3 = builder
            .withData(enemyTiles, sizeof(enemyTiles))
            .withSize(SIZE_16_16)
            .withLocation(enemy3X, enemy3Y)
            .buildPtr();
    enemy3->setStayWithinBounds(false);
    */

    playerX = 48;
    playerY = 128;
    isText = false;
    currentDir = Direction::UP;
    scrollY = 95;
    bg->scroll(0,scrollY);
    appleSpeed = 3;
    bulletSpeed = 1;
    shootSpeed = 50;
    cooldown = shootSpeed;

    linkHP = 1;
    enemy1HP = 3;
    enemy2HP = 3;
    //enemy3HP = 3;

    enemyCD = 0;

    enemy1Dead = false;
    enemy2Dead = false;
    //enemy3Dead = false;

    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);

    bg = std::unique_ptr<Background>(new Background(1, CityBGTiles, sizeof(CityBGTiles), City_Map, sizeof(City_Map)));
    bg.get()->useMapScreenBlock(16);
}

void CityScene::tick(u16 keys) {

    if(!linkAnimation.get()->isOffScreen() && linkHP != 0) {
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
            isNextTileGo = mControl2.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 2);
            if (playerX <= GBA_SCREEN_WIDTH - linkAnimation.get()->getWidth()) {
                if (isNextTileGo) {
                    playerX++;
                    linkAnimation->makeAnimated(4, 5, 12);
                    if(keys & KEY_A){
                        shoot();
                    }
                }
            }

        } else if (keys & KEY_UP) {
            currentDir = Direction::UP;
            isNextTileGo = mControl2.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 2);
            if (playerY > 1) {
                if (isNextTileGo) {
                    playerY--;
                    linkAnimation->makeAnimated(6, 5, 0);
                    if(keys & KEY_A){
                        shoot();
                    }
                }
            }
        } else if (keys & KEY_LEFT) {
            currentDir = Direction::LEFT;
            linkAnimation->flipHorizontally(false);
            isNextTileGo = mControl2.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 2);
            if (playerX > 1) {
                if (isNextTileGo) {
                    playerX--;
                    linkAnimation->makeAnimated(4, 5, 12);
                    if(keys & KEY_A){
                        shoot();
                    }
                }
            }
        } else if (keys & KEY_DOWN) {
            currentDir = Direction::DOWN;
            isNextTileGo = mControl2.isNextTileGo(playerX, playerY, scrollX, scrollY, currentDir, 2);
            if (playerY <= GBA_SCREEN_HEIGHT - linkAnimation.get()->getHeight()) {
                if (isNextTileGo) {
                    playerY++;
                    linkAnimation->makeAnimated(6, 5, 6);
                    if(keys & KEY_A){
                        shoot();
                    }
                }
            }
        } else if (keys & KEY_A) {
            shoot();
        } else if (!keys) {
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
            TextStream::instance().setText("Pink Lloydie Square", 12, 10);
            TextStream::instance().setText("----->", 14, 10);
            isText = true;
        } else if (isText) {
            isText = false;
            TextStream::instance().clear();
        }

        if (apple->collidesWith(*enemy1)){
            apple->moveTo(1,500);
            enemy1HP--;
            if(enemy1HP == 0){
                enemy1Dead = true;
                enemy1->moveTo(-100, 25);
            }
        } else if (apple->collidesWith(*enemy2)){
            apple->moveTo(1,500);
            enemy2HP--;
            if(enemy2HP <= 0){
                enemy2Dead = true;
                enemy2->moveTo(-100, 50);
            }
        } /* else if (apple->collidesWith(*enemy3)){
            apple->moveTo(1,500);
            enemy3HP--;
            if(enemy3HP <= 0){
                enemy3Dead = true;
                enemy3->moveTo(-100, 75);
            }
        }
        */

        if (bullet1->collidesWith(*linkAnimation)) {
            bullet1->moveTo(1, 550);
            linkHP--;
        } else if (bullet2->collidesWith(*linkAnimation)) {
            bullet2->moveTo(1, 600);
            linkHP--;
        }/* else if (bullet3->collidesWith(*linkAnimation)) {
            bullet3->moveTo(1, 650);
            linkHP--;
        }
        */

        //animation van de enemies maakt het level heel traag
        /*
        enemy1->makeAnimated(3,11,0);
        enemy2->makeAnimated(3,9,0);
        enemy3->makeAnimated(3,13,-1); //fixt bug waarbij laatste enemy zijn laatste frame fout is
        */


        if(!apple->isOffScreen()){
            appleX += appledx;
            appleY += appledy;
        } else {
            appleX = 300;
            appleY = 300;
        }

        if(!bullet1->isOffScreen()){
            bullet1X += bullet1dx;
            bullet1Y += bullet1dy;
        } else {
            bullet1X = 300;
            bullet1Y = 550;
        }

        if(!bullet2->isOffScreen()){
            bullet2X += bullet2dx;
            bullet2Y += bullet2dy;
        } else {
            bullet2X = 300;
            bullet2Y = 600;
        }

        /*
        if(!bullet3->isOffScreen()){
            bullet3X += bullet3dx;
            bullet3Y += bullet3dy;
        } else {
            bullet3X = 300;
            bullet3Y = 650;
        }
        */

        enemyCD++;
        if(enemyCD == 40 && !enemy1Dead){
            enemyshoot(1);
        } else if(enemyCD == 80 && !enemy2Dead){
            enemyshoot(2);
        } /*else if(enemyCD == 120 && !enemy3Dead){
            enemyshoot(3);
        } */else if(enemyCD>80){
            enemyCD = 0;
        }

        linkAnimation->moveTo(playerX, playerY);
        apple->moveTo(appleX, appleY);
        sign->moveTo(190,90-scrollY);
        bullet1->moveTo(bullet1X, bullet1Y-scrollY);
        bullet2->moveTo(bullet2X, bullet2Y-scrollY);
        //bullet3->moveTo(bullet3X, bullet3Y-scrollY);
        if(!enemy1Dead){
            enemy1->moveTo(enemy1X,enemy1Y-scrollY);
        }
        if(!enemy2Dead){
            enemy2->moveTo(enemy2X,enemy2Y-scrollY);
        }
        /*
        if(!enemy3Dead){
            enemy3->moveTo(enemy3X,enemy3Y-scrollY);
        }
        */

    }
    if (cooldown < shootSpeed) {
        cooldown++;
    }

    if(linkHP == 0){
        //linkAnimation->animateToFrame(linkAnimation->getCurrentFrame());
        TextStream::instance().setText("YOU DIED,", 6, 2);
        TextStream::instance().setText("FRUIT EATING SCUM.", 7, 2);
        TextStream::instance().setText("WINDOWS WILL RULE THE WORLD", 9, 2);
        TextStream::instance().setText(".", 10, 2);
        TextStream::instance().setText(".", 11, 2);
        TextStream::instance().setText(".", 12, 2);
        TextStream::instance().setText("FOREVER!!!", 13, 2);
    }
}

void CityScene::shoot(){
    if (cooldown == shootSpeed) {
        if (currentDir == Direction::UP) {
            appleX = playerX + 12;
            appleY = playerY;
            appledx = 0;
            appledy = -appleSpeed;
        } else if (currentDir == Direction::DOWN) {
            appleX = playerX + 12;
            appleY = playerY + 24;
            appledx = 0;
            appledy = appleSpeed;
        } else if (currentDir == Direction::LEFT) {
            appleX = playerX;
            appleY = playerY + 16;
            appledx = -appleSpeed;
            appledy = 0;
        } else { //currentDir == Direction::RIGHT
            appleX = playerX + 24;
            appleY = playerY + 16;
            appledx = appleSpeed;
            appledy = 0;
        }
        apple->moveTo(appleX, appleY);
        cooldown = 0;
    }
}

void CityScene::enemyshoot(int enemy) {
    int direction = rand() % 4 + 1; // enemy schient in een random richting
    switch (enemy) {
        case 1 : {
            switch (direction) {
                case 1 : {
                    bullet1dx = bulletSpeed;
                    bullet1dy = -bulletSpeed;
                    break;
                }
                case 2 : {
                    bullet1dx = bulletSpeed*2;
                    bullet1dy = 0;
                    break;
                }
                case 3 : {
                    bullet1dx = bulletSpeed;
                    bullet1dy = bulletSpeed;
                    break;
                }
                case 4 : {
                    bullet1dx = 0;
                    bullet1dy = bulletSpeed*2;
                    break;
                }
            }
            bullet1X = enemy1X+4;
            bullet1Y = enemy1Y+4;
            bullet1->moveTo(bullet1X, bullet1Y);
            break;
        }
        case 2 : {
            switch (direction) {
                case 1 : {
                    bullet2dx = -bulletSpeed*2;
                    bullet2dy = 0;
                    break;
                }
                case 2 : {
                    bullet2dx = -bulletSpeed;
                    bullet2dy = -bulletSpeed;
                    break;
                }
                case 3 : {
                    bullet2dx = 0;
                    bullet2dy = -bulletSpeed*2;
                    break;
                }
                case 4 : {
                    bullet2dx = bulletSpeed;
                    bullet2dy = -bulletSpeed;
                    break;
                }
            }
            bullet2X = enemy2X+4;
            bullet2Y = enemy2Y+4;
            bullet2->moveTo(bullet2X, bullet2Y);
            break;
        }
        /*
        case 3 : {
            switch (direction) {
                case 1 : {
                    bullet3dx = bulletSpeed;
                    bullet3dy = bulletSpeed;
                    break;
                }
                case 2 : {
                    bullet3dx = 0;
                    bullet3dy = bulletSpeed*2;
                    break;
                }
                case 3 : {
                    bullet3dx = -bulletSpeed;
                    bullet3dy = bulletSpeed;
                    break;
                }
                case 4 : {
                    bullet3dx = -bulletSpeed*2;
                    bullet3dy = 0;
                    break;
                }
            }
            bullet3X = enemy3X+4;
            bullet3Y = enemy3Y+4;
            bullet3->moveTo(bullet3X, bullet3Y);
            break;

        }
        */
    }
}