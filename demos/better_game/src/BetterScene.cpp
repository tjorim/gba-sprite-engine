//
// Created by ubuntu on 29.11.18.
//

#include "BetterScene.h"
//#include "castleworker.h"
#include "background.h"
#include "pats.h"
#include "dead.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <libgba-sprite-engine/background/text_stream.h>
#include <sstream>

#define PLAYER_TRANSLATION_DIFF 1
#define PLAYER_UPDOWN 1

std::vector<Sprite *> BetterScene::sprites() {
    //TextStream::instance().setText(, 1,1);
    return{
            mooi_sprite.get(), mooi_sprite1.get()  , eendje.get() , gunpowder.get() , gunpowder2.get(), bom.get() ,
            bom2.get() , kist.get(), kist2.get(), ladderGroot.get(), ladderHoofd.get(), ladderGroot2.get(), ladderGroot3.get(),
            ladderGroot4.get(), kanon.get(), kanon2.get(), ladderHoofd2.get(), ladderHoofd3.get(),
            enemy->getSprite()
    };

}
std::vector<Background *> BetterScene::backgrounds() {
    return{
            bg.get()
    };
}
void BetterScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;

    mooi_sprite = builder
            .withData(CastleWorkerGrijsTiles, sizeof(CastleWorkerGrijsTiles))
            .withSize(SIZE_16_16)
            .withLocation(70,105)
            .buildPtr();

    mooi_sprite1 = builder
            .withData(CastleWorkerGrijsTiles, sizeof(CastleWorkerGrijsTiles))
            .withSize(SIZE_16_16)
            .withLocation(110,57)
            .buildPtr();

    eendje = builder
            .withData(DuckyGrijsTiles, sizeof(DuckyGrijsTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH + 20, 135)
            .buildPtr();

    ladderGroot = builder
            .withData(ladder8x32Tiles, sizeof(ladder8x32Tiles))
            .withSize(SIZE_8_32)
            .withLocation(40, 128)
            .buildPtr();

    ladderGroot2 = builder
            .withData(ladder8x32Tiles, sizeof(ladder8x32Tiles))
            .withSize(SIZE_8_32)
            .withLocation(60,88)
            .buildPtr();

    ladderGroot3 = builder
            .withData(ladder8x32Tiles, sizeof(ladder8x32Tiles))
            .withSize(SIZE_8_32)
            .withLocation(91,168)
            .buildPtr();

    ladderGroot4 = builder
            .withData(ladder8x32Tiles, sizeof(ladder8x32Tiles))
            .withSize(SIZE_8_32)
            .withLocation(91,200)
            .buildPtr();

    ladderHoofd = builder
            .withData(ladderhoofd8x8Tiles, sizeof(ladderhoofd8x8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(90,155)
            .buildPtr();

    ladderHoofd2 = builder
            .withData(ladderhoofd8x8Tiles, sizeof(ladderhoofd8x8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(39,112)
            .buildPtr();

    ladderHoofd3 = builder
            .withData(ladderhoofd8x8Tiles, sizeof(ladderhoofd8x8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(59,65)
            .buildPtr();

    kist = builder
            .withData(flatchestTiles, sizeof(flatchestTiles))
            .withSize(SIZE_32_32)
            .withLocation(125, 202)
            .buildPtr();

    kist2 = builder
            .withData(flatchestTiles, sizeof(flatchestTiles))
            .withSize(SIZE_32_32)
            .withLocation(25, 202)
            .buildPtr();

    kanon = builder
            .withData(flatkanonTiles, sizeof(flatkanonTiles))
            .withSize(SIZE_32_32)
            .withLocation(143, 93)
            .buildPtr();

    kanon2 = builder
            .withData(flatkanonTiles, sizeof(flatkanonTiles))
            .withSize(SIZE_32_32)
            .withLocation(143, 45)
            .buildPtr();

    bom = builder
            .withData(bombGrijsTiles, sizeof(bombGrijsTiles))
            .withSize(SIZE_16_16)
            .withLocation(28, 188)
            .buildPtr();

    bom2 = builder
            .withData(bombGrijsTiles, sizeof(bombGrijsTiles))
            .withSize(SIZE_16_16)
            .withLocation(38, 188)
            .buildPtr();

    gunpowder = builder
            .withData(gunpowderTiles, sizeof(gunpowderTiles))
            .withSize(SIZE_16_16)
            .withLocation(125, 188)
            .buildPtr();

    gunpowder2 = builder
            .withData(gunpowderTiles, sizeof(gunpowderTiles))
            .withSize(SIZE_16_16)
            .withLocation(140, 188)
            .buildPtr();

    //enemy = new Enemy(builder.withLocation(20,30).buildWithDataOf(*eendje.get()));
    enemy = new Enemy(builder
                              .withData(DuckyGrijsTiles, sizeof(DuckyGrijsTiles))
                              .withSize(SIZE_16_16)
                              .withLocation(240, 135)
                              .buildPtr());

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(14);

    scrollY = 10;
    scrollX = 8;
    prevScrollY = 0;
    prevScrollX = 0;
    syncScroll();



}
void BetterScene::tick(u16 keys) {
    if (engine->getTimer()->getTotalMsecs() < 5000) {
        counter++;
    } else {
        engine->getTimer()->stop();
        if(eendje->getX() > 152 + prevScrollX) {
            eendje->moveTo(eendje->getX() - 1, eendje->getY());
        }
    }

    eendje->flipHorizontally(true);

    enemy->update();
    //TextStream::instance().setText(std::string("POS: ") + std::to_string(enemy->getX()), 2,0);

    if(enemy->getX() == 160){
        --health;
        engine.get()->enqueueSound(pats, sizeof(pats), 32000);
    }
    TextStream::instance().setText(std::to_string(health) + std::string(" / 250"), 0,70);
    TextStream::instance().setText(std::string("Kills: ") + std::to_string(killCounter) + std::string(" / 10"), 1,70);

    /*mooi_sprite->animateToFrame(0);
    mooi_sprite1->animateToFrame(0);
    eendje->animateToFrame(0);
    kist->animateToFrame(0);
    kist2->animateToFrame(0);
    ladderHoofd->animateToFrame(0);
    ladderHoofd2->animateToFrame(0);
    ladderHoofd3->animateToFrame(0);
    ladderGroot->animateToFrame(0);
    ladderGroot2->animateToFrame(0);
    ladderGroot3->animateToFrame(0);
    ladderGroot4->animateToFrame(0);
    kanon->animateToFrame(0);
    kanon2->animateToFrame(0);
    bom->animateToFrame(0);
    bom2->animateToFrame(0);
    gunpowder->animateToFrame(0);
    gunpowder2->animateToFrame(0);*/

    if(keys & KEY_L && !switchLock){
        currentPlayer = currentPlayer+1;
        switchLock = true;
    }
    if(currentPlayer >= 2){
        currentPlayer = 0;
    }
    if(switchLock && !keys&&KEY_L){
        switchLock= false;
    }
    //mooi_sprite.get()->moveTo(mooi_sprite.get()->getX(),mooi_sprite->getY()+1);
    if(currentPlayer == 0) {
        if (keys & KEY_LEFT && mooi_sprite->getX() > 30 - scrollX && mooi_sprite->getY() == 105 - scrollY ||
            keys & KEY_LEFT && mooi_sprite->getX() > 45 - scrollX && mooi_sprite->getY() == 57 -scrollY ||
            keys & KEY_LEFT && mooi_sprite->getX() > 30 - scrollX && mooi_sprite->getY() == 145 - scrollY ||
            keys & KEY_LEFT && mooi_sprite->getX() > 30 - scrollX && mooi_sprite->getY() == 217 - scrollY) {
            mooi_sprite->flipHorizontally(false);
            player1TranslationH -= PLAYER_TRANSLATION_DIFF;
        } else if (keys & KEY_RIGHT && mooi_sprite->getX() < 145 - scrollX && mooi_sprite->getY() == 105 - scrollY ||
                   keys & KEY_RIGHT && mooi_sprite->getX() < 145 - scrollX && mooi_sprite->getY() == 57 - scrollY ||
                   keys & KEY_RIGHT && mooi_sprite->getX() < 145 - scrollX && mooi_sprite->getY() == 145 - scrollY ||
                   keys & KEY_RIGHT && mooi_sprite->getX() < 145 - scrollX && mooi_sprite->getY() == 217 - scrollY) {
            mooi_sprite->flipHorizontally(true);
            player1TranslationH += PLAYER_TRANSLATION_DIFF;
        } else if (keys & KEY_UP) {
            interactUp(*mooi_sprite, currentPlayer);
            //player1TranslationV -= PLAYER_UPDOWN;
        } else if (keys & KEY_DOWN) {
            interactDown(*mooi_sprite,currentPlayer);
            //player1TranslationV += PLAYER_UPDOWN;
        }


    }
    else if (currentPlayer == 1) {
        if (keys & KEY_LEFT && mooi_sprite1->getX() > 30 - scrollX && mooi_sprite1->getY() == 105 - scrollY ||
            keys & KEY_LEFT && mooi_sprite1->getX() > 45 - scrollX && mooi_sprite1->getY() == 57 - scrollY ||
            keys & KEY_LEFT && mooi_sprite1->getX() > 30 - scrollX && mooi_sprite1->getY() == 145 - scrollY||
            keys & KEY_LEFT && mooi_sprite1->getX() > 30 - scrollX && mooi_sprite1->getY() == 217 - scrollY) {
            mooi_sprite1->flipHorizontally(false);
            player2TranslationH -= PLAYER_TRANSLATION_DIFF;
        } else if (keys & KEY_RIGHT && mooi_sprite1->getX() < 145 - scrollX && mooi_sprite1->getY() == 105 - scrollY ||
                   keys & KEY_RIGHT && mooi_sprite1->getX() < 145 - scrollX && mooi_sprite1->getY() == 57 - scrollY ||
                   keys & KEY_RIGHT && mooi_sprite1->getX() < 145 - scrollX && mooi_sprite1->getY() == 145 - scrollY||
                   keys & KEY_RIGHT && mooi_sprite1->getX() < 145 - scrollX && mooi_sprite1->getY() == 217 - scrollY) {
            mooi_sprite1->flipHorizontally(true);
            player2TranslationH += PLAYER_TRANSLATION_DIFF;
        } else if (keys & KEY_UP) {
            interactUp(*mooi_sprite1, currentPlayer);
        } else if (keys & KEY_DOWN) {
            interactDown(*mooi_sprite1, currentPlayer);
        }



    }
    mooi_sprite->moveTo(player1TranslationH - scrollX, player1TranslationV - scrollY);
    mooi_sprite1->moveTo(player2TranslationH - scrollX, player2TranslationV - scrollY);

    if(health == 0 || killCounter == 10){
        gameOver();
    }

}

void BetterScene::syncScroll(){
    bg.get()->scroll(scrollX , scrollY);

    //mooi_sprite->moveTo(mooi_sprite->getX() - scrollX, mooi_sprite->getY() - scrollY);
    //mooi_sprite1->moveTo(mooi_sprite1->getX() - scrollX, mooi_sprite1->getY() - scrollY);
    eendje->moveTo(eendje->getX() - scrollX + prevScrollX , eendje->getY() - scrollY + prevScrollY);
    kist->moveTo(kist->getX() - scrollX + prevScrollX, kist->getY() - scrollY + prevScrollY);
    kist2->moveTo(kist2->getX() - scrollX + prevScrollX, kist2->getY() - scrollY + prevScrollY);
    ladderHoofd->moveTo(ladderHoofd->getX() - scrollX + prevScrollX, ladderHoofd->getY() - scrollY + prevScrollY);
    ladderHoofd2->moveTo(ladderHoofd2->getX() - scrollX + prevScrollX, ladderHoofd2->getY() - scrollY + prevScrollY);
    ladderHoofd3->moveTo(ladderHoofd3->getX() - scrollX + prevScrollX, ladderHoofd3->getY() - scrollY + prevScrollY);
    ladderGroot->moveTo(ladderGroot->getX() - scrollX + prevScrollX, ladderGroot->getY() - scrollY + prevScrollY);
    ladderGroot2->moveTo(ladderGroot2->getX() - scrollX + prevScrollX, ladderGroot2->getY() - scrollY + prevScrollY);
    ladderGroot3->moveTo(ladderGroot3->getX() - scrollX + prevScrollX, ladderGroot3->getY() - scrollY + prevScrollY);
    ladderGroot4->moveTo(ladderGroot4->getX() - scrollX + prevScrollX, ladderGroot4->getY() - scrollY + prevScrollY);
    kanon->moveTo(kanon->getX() - scrollX + prevScrollX, kanon->getY() - scrollY + prevScrollY);
    kanon2->moveTo(kanon2->getX() - scrollX + prevScrollX, kanon2->getY() - scrollY + prevScrollY);

    mooi_sprite->moveTo(player1TranslationH - scrollX + prevScrollX, player1TranslationV - scrollY + prevScrollY);
    mooi_sprite1->moveTo(player2TranslationH - scrollX + prevScrollX, player2TranslationV - scrollY + prevScrollY);
    bom->moveTo(bom->getX() - scrollX + prevScrollX, bom->getY() - scrollY + prevScrollY);
    bom2->moveTo(bom2->getX() - scrollX + prevScrollX, bom2->getY() - scrollY + prevScrollY);

    gunpowder->moveTo(gunpowder->getX() - scrollX + prevScrollX, gunpowder->getY() - scrollY + prevScrollY);
    gunpowder2->moveTo(gunpowder2->getX() - scrollX + prevScrollX, gunpowder2->getY() - scrollY + prevScrollY);


    enemy->setY(enemy->getY() - scrollY + prevScrollY);
    enemy->getSprite()->moveTo(enemy->getX(), enemy->getY());

    prevScrollX = scrollX;
    prevScrollY = scrollY;

}
void BetterScene::interactUp(Sprite &sprite , int cPlayer) {

    if (currentPlayer == 0) {
        if (ladderGroot->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV - 40;
        }
        if (ladderGroot2->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV - 48;
        }
        if (ladderGroot4->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV - 72;
            scrollY = 10;
        }
        if(kist2->collidesWith(sprite)){ //bom

            if(player1Bom == 0 ){
                if(bomVolg == 0){player1Bom = 1; bomVolg = 1; bom->moveTo(-20,-20);}
                else if(bom2Volg == 0){player1Bom = 1; bom2Volg = 1; bom2->moveTo(-20,-20);}
            }
        }
        if(kist->collidesWith(sprite)){ //gunpowder
            if(player1Gunpowder == 0){
                if(gunpowderVolg == 0){player1Gunpowder = 1; gunpowderVolg = 1; gunpowder->moveTo(-20,-20);}
                else if(gunpowder2Volg == 0){player1Gunpowder = 1; gunpowder2Volg = 1; gunpowder2->moveTo(-20,-20); }
            }
        }
        if(kanon->collidesWith(sprite) && kanonGunpowder == 1 && kanonBom == 1){ //fire
            kanonBom = 0; kanonGunpowder = 0;
            if(kanon->collidesWith(*bom)){bom->moveTo(28,188); bomVolg = 0;}
            else{
                bom2->moveTo(38,188); bom2Volg = 0;
            }
            if(kanon->collidesWith(*gunpowder))
            {
                gunpowder->moveTo(125,188); gunpowderVolg = 0;
                if(enemy->getX() < 200) {
                    enemy->kill();
                    ++killCounter;
                }
            }
            else{
                gunpowder2->moveTo(145,188); gunpowder2Volg = 0;
                if(enemy->getX() < 200) {
                    enemy->kill();
                    ++killCounter;
                }
            }
        }
        if(kanon2->collidesWith(sprite) && kanon2Gunpowder == 1 && kanon2Bom == 1){ //fire
            kanon2Bom = 0; kanon2Gunpowder = 0;
            if(kanon2->collidesWith(*bom)){bom->moveTo(28,188); bomVolg = 0;}
            else{
                bom2->moveTo(38,188); bom2Volg = 0;
            }
            if(kanon2->collidesWith(*gunpowder)){
                gunpowder->moveTo(125,188); gunpowderVolg = 0;
                if(enemy->getX() > 200 && enemy->getX() < 240) {
                    enemy->kill();
                    ++killCounter;
                }
            }
            else{
                gunpowder2->moveTo(145,188); gunpowder2Volg = 0;
                if(enemy->getX() > 200 && enemy->getX() < 240) {
                    enemy->kill();
                    ++killCounter;
                }
            }
        }


    }


    else if(currentPlayer == 1){
        if (ladderGroot->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV - 40;

        }
        if (ladderGroot2->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV - 48;
        }
        if (ladderGroot4->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV - 72;
            scrollY = 10;
        }

        if(kist2->collidesWith(sprite)){ //bom

            if(player2Bom == 0 ){
                if(bomVolg == 0){player2Bom = 1; bomVolg = 1; bom->moveTo(-20,-20);}
                else if(bom2Volg == 0){player2Bom = 1; bom2Volg = 1; bom2->moveTo(-20,-20);}
            }
        }
        if(kist->collidesWith(sprite)){ //gunpowder
            if(player2Gunpowder == 0){
                if(gunpowderVolg == 0){player2Gunpowder = 1; gunpowderVolg = 1; gunpowder->moveTo(-20,-20);}
                else if(gunpowder2Volg == 0){player2Gunpowder = 1; gunpowder2Volg = 1; gunpowder2->moveTo(-20,-20); }
            }
        }

        if(kanon->collidesWith(sprite) && kanonGunpowder == 1 && kanonBom == 1){ //fire
            kanonBom = 0; kanonGunpowder = 0;
            if(kanon->collidesWith(*bom)){bom->moveTo(28,188); bomVolg = 0;}
            else{
                bom2->moveTo(38,188); bom2Volg = 0;
            }
            if(kanon->collidesWith(*gunpowder)){gunpowder->moveTo(125,188); gunpowderVolg = 0;}
            else{
                gunpowder2->moveTo(145,188); gunpowder2Volg = 0;
            }
        }
        if(kanon2->collidesWith(sprite) && kanon2Gunpowder == 1 && kanon2Bom == 1){ //fire
            kanon2Bom = 0; kanon2Gunpowder = 0;
            if(kanon2->collidesWith(*bom)){bom->moveTo(28,188); bomVolg = 0;}
            else{
                bom2->moveTo(38,188); bom2Volg = 0;
            }
            if(kanon2->collidesWith(*gunpowder)){gunpowder->moveTo(125,188); gunpowderVolg = 0;}
            else{
                gunpowder2->moveTo(145,188); gunpowder2Volg = 0;
            }
        }


    }
    syncScroll();
}


void BetterScene::interactDown(Sprite &sprite, int cPlayer) {


    if (currentPlayer == 0) {
        if (ladderHoofd->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV + 72;
            scrollY = 100;
            syncScroll();
        }
        if (ladderHoofd2->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV + 40;
        }
        if (ladderHoofd3->collidesWith(sprite)) {
            player1TranslationV = player1TranslationV + 48;
        }
        if(kanon->collidesWith(sprite) && player1Bom == 1 && bomVolg == 1 && kanonBom == 0){
            kanonBom = 1; player1Bom = 0; bomVolg = 2;
            bom->moveTo(kanon->getX()+10, kanon->getY());
        }
        if(kanon->collidesWith(sprite) && player1Bom == 1 && bom2Volg == 1 && kanonBom == 0){
            kanonBom = 1; player1Bom = 0; bom2Volg = 2;
            bom2->moveTo(kanon->getX()+10, kanon->getY());
        }
        if(kanon2->collidesWith(sprite) && player1Bom == 1 && bomVolg == 1 && kanon2Bom == 0){
            kanon2Bom = 1; player1Bom = 0; bomVolg = 2;
            bom->moveTo(kanon2->getX()+10, kanon2->getY());
        }
        if(kanon2->collidesWith(sprite) && player1Bom == 1 && bom2Volg == 1 && kanon2Bom == 0){
            kanon2Bom = 1; player1Bom = 0; bom2Volg = 2;
            bom2->moveTo(kanon2->getX()+10, kanon2->getY());
        }

        if(kanon->collidesWith(sprite) && player1Gunpowder == 1 && gunpowderVolg == 1 && kanonGunpowder == 0){
            kanonGunpowder = 1; player1Gunpowder = 0; gunpowderVolg = 2;
            gunpowder->moveTo(kanon->getX() -5, kanon->getY());
        }
        if(kanon->collidesWith(sprite) && player1Gunpowder == 1 && gunpowder2Volg == 1 && kanonGunpowder == 0){
            kanonGunpowder = 1; player1Gunpowder = 0; gunpowder2Volg = 2;
            gunpowder2->moveTo(kanon->getX() -5, kanon->getY());
        }
        if(kanon2->collidesWith(sprite) && player1Gunpowder == 1 && gunpowderVolg == 1 && kanon2Gunpowder == 0){
            kanon2Gunpowder = 1; player1Gunpowder = 0; gunpowderVolg = 2;
            gunpowder->moveTo(kanon2->getX() -5, kanon2->getY());
        }
        if(kanon2->collidesWith(sprite) && player1Gunpowder == 1 && gunpowder2Volg == 1 && kanon2Gunpowder == 0){
            kanon2Gunpowder = 1; player1Gunpowder = 0; gunpowder2Volg = 2;
            gunpowder2->moveTo(kanon2->getX()-5, kanon2->getY());
        }







    } else if (currentPlayer == 1) {
        if (ladderHoofd->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV + 72;
            scrollY = 100;
            syncScroll();
        }
        if (ladderHoofd2->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV + 40;
        }
        if (ladderHoofd3->collidesWith(sprite)) {
            player2TranslationV = player2TranslationV + 48;
            syncScroll();
        }

        if(kanon->collidesWith(sprite) && player2Bom == 1 && bomVolg == 1 && kanonBom == 0){
            kanonBom = 1; player2Bom = 0; bomVolg = 2;
            bom->moveTo(kanon->getX()+10, kanon->getY());
        }
        if(kanon->collidesWith(sprite) && player2Bom == 1 && bom2Volg == 1 && kanonBom == 0){
            kanonBom = 1; player2Bom = 0; bom2Volg = 2;
            bom2->moveTo(kanon->getX()+10, kanon->getY());
        }
        if(kanon2->collidesWith(sprite) && player2Bom == 1 && bomVolg == 1 && kanon2Bom == 0){
            kanon2Bom = 1; player2Bom = 0; bomVolg = 2;
            bom->moveTo(kanon2->getX()+10, kanon2->getY());
        }
        if(kanon2->collidesWith(sprite) && player2Bom == 1 && bom2Volg == 1 && kanon2Bom == 0){
            kanon2Bom = 1; player2Bom = 0; bom2Volg = 2;
            bom2->moveTo(kanon2->getX()+10, kanon2->getY());
        }

        if(kanon->collidesWith(sprite) && player2Gunpowder == 1 && gunpowderVolg == 1 && kanonGunpowder == 0){
            kanonGunpowder = 1; player2Gunpowder = 0; gunpowderVolg = 2;
            gunpowder->moveTo(kanon->getX() -5 , kanon->getY());
        }
        if(kanon->collidesWith(sprite) && player2Gunpowder == 1 && gunpowder2Volg == 1 && kanonGunpowder == 0){
            kanonGunpowder = 1; player2Gunpowder = 0; gunpowder2Volg = 2;
            gunpowder2->moveTo(kanon->getX() -5, kanon->getY());
        }
        if(kanon2->collidesWith(sprite) && player2Gunpowder == 1 && gunpowderVolg == 1 && kanon2Gunpowder == 0){
            kanon2Gunpowder = 1; player2Gunpowder = 0; gunpowderVolg = 2;
            gunpowder->moveTo(kanon2->getX() -5, kanon2->getY());
        }
        if(kanon2->collidesWith(sprite) && player2Gunpowder == 1 && gunpowder2Volg == 1 && kanon2Gunpowder == 0){
            kanon2Gunpowder = 1; player2Gunpowder = 0; gunpowder2Volg = 2;
            gunpowder2->moveTo(kanon2->getX()-5 , kanon2->getY());
        }


    }

}

void BetterScene::gameOver() {
    bool dood = false;
    while(true){
        if(health == 0 &&!dood){
            TextStream::instance().setText("Game over", 10, 10);
            engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
            dood = true;
        }else if (killCounter == 10){
            TextStream::instance().setText("You won", 10,10);
        }
    }
}
