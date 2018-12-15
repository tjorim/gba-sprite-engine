//
// Created by joost on 6/12/2018.
//

#include "scene_level1.h"

//
// Created by Wouter Groeneveld on 28/07/18.
//
#include <string>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Sonic_sprites.h"
#include "scene_level1.h"
#include "background_level1.h"

std::vector<Sprite *> SceneLevel1::sprites() {
    return {
            sonic.get()
    };
}

std::vector<Background *> SceneLevel1::backgrounds() {
    return {
            bg.get()
    };
}

void SceneLevel1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(Sonic_sprites_32_32Pal, sizeof(Sonic_sprites_32_32Pal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(BackgroundLevel1Pal, sizeof(BackgroundLevel1Pal)));

    bg = std::unique_ptr<Background>(new Background(1, BackgroundLevel1Tiles, sizeof(BackgroundLevel1Tiles), map_level1, sizeof(map_level1)));
    bg.get()->useMapScreenBlock(16);

    bg->scroll(scrollX,scrollY);

    engine->setNullptrAsCurrentEffectForTransistion(); //currentEffectForTransition terug nullptr maken om te zorgen dat het mogelijk is om de scene opnieuw te laden als je dood bent. want anders geeft !engine->isTransitioning() na 1 keer altijd true.

    SpriteBuilder<AffineSprite> affineBuilder;

    sonic = affineBuilder
            .withData(Sonic_sprites_32_32Tiles, sizeof(Sonic_sprites_32_32Tiles))
            .withSize(SIZE_32_32)
            .withAnimated(4,10)
            .withLocation(GBA_SCREEN_WIDTH - 200, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();




    sonic->stopAnimating();
    TextStream::instance() << "level 1" << "intro";
    //TextStream::instance().setText("x:" + std::to_string(sonic->getX()), 3, 8);
    //TextStream::instance().setText("y:" + std::to_string(sonic->getX()), 4, 8);


}

Timer timer;
//statussen over de speler kan in Player.h gedefinieerd worden. Dit was om snel te testen.
bool runningState = false;
bool isBall = false;
bool canTakeDamage = true;
int ballspeed = 1;

void SceneLevel1::tick(u16 keys) {

    timer.onvblank();// geeft ticks aan timer maar timer gaat pas vooruit wanneer timer.start();


    TextStream::instance().setText("x:" + std::to_string(sonic->getX()), 2, 1);
    TextStream::instance().setText("y:" + std::to_string(sonic->getY()), 3, 1);
    TextStream::instance().setText("HP : " + std::to_string(player->getAantalLevens()), 17, 1);
    //TextStream::instance().setText("scrollY:" + std::to_string(scrollY), 4, 1);
    TextStream::instance().setText("Timer:" + std::to_string(timer.getSecs()), 4, 1);
    TextStream::instance().setFontColor(0x080F);

    if(!(keys & KEY_LEFT) && !(keys & KEY_RIGHT)){
        sonic->stopAnimating();
        sonic->animateToFrame(4);
        runningState = false;
        TextStream::instance().setText("IDLE", 6, 2);
    }
    else{
        TextStream::instance().setText("ACTIVE", 6, 1);
        if(keys & KEY_RIGHT){
            if(sonic->getVelocity().y == 0)  //setvelocity  ;
                if(!runningState && !isBall) {
                    sonic->makeAnimated(6,5,6); //makeAnimated(frames,delay,Startframe)
                    runningState = true;
                    TextStream::instance().setText("RIGHT", 5, 1);
                }
            if(isBall) scrollX += ballspeed;
            bg->scroll(scrollX++ ,scrollY); // als isball = false --> gewoon 1 stap
        }

        if(keys & KEY_LEFT){
            if(sonic->getVelocity().y == 0)  //setvelocity  ;
                if(!runningState && !isBall) {
                    sonic->makeAnimated(6,5,14);
                    runningState = true;
                    TextStream::instance().setText("LEFT", 5, 1);

                }
            if(isBall) scrollX -= ballspeed;
            bg->scroll(scrollX--,scrollY);
        }

    }







    if(keys & KEY_UP){ // springen --> later in variabelen steken van Player
        if(sonic->getY() == GBA_SCREEN_HEIGHT - 60){
            sonic->setVelocity(0,-3);
            TextStream::instance().setText("JUMP", 5, 2);

        }
    }


    if(keys & KEY_DOWN){
        if(!isBall) {
            isBall = true;
            sonic->makeAnimated(4,5,0); //makeAnimated(frames,delay,Startframe)
            TextStream::instance().setText("BALL", 5, 2);
        }
    }
    if(keys & KEY_A && canTakeDamage){ //HIT DETECTION met timer anders gaat HP veel te snel omlaag
        player->setAantalLevens(player->getAantalLevens()-1);
        timer.start();
        canTakeDamage = false;
    }
    else if(keys & KEY_A && !canTakeDamage){
        if(timer.getSecs() >= 1){
            timer.reset();
            canTakeDamage = true;
        }
    }

    if(!runningState) isBall = false;

/*
    if(keys & KEY_UP){
        if(sonic->getY() == GBA_SCREEN_HEIGHT/2) sonic->setVelocity(0,-1);
        sonic->animateToFrame(0);
    }


    else{
        if(sonic->getY() == GBA_SCREEN_HEIGHT/2) {
            sonic->setVelocity(0, 0);
            if(!(keys & KEY_RIGHT)) sonic->animateToFrame(0);
        }
    }
    */
    if(sonic->getY() <= GBA_SCREEN_HEIGHT - 110) sonic->setVelocity(0,3);
    if(sonic->getY() == GBA_SCREEN_HEIGHT - 60 && sonic->getVelocity().y == 3){
        sonic->setVelocity(0,0);
        TextStream::instance().setText("RESET JUMP", 5, 2);
    }

    if(player->getAantalLevens() == 0 && !engine->isTransitioning()){
        engine->transitionIntoScene(new SceneLevel1(engine), new FadeOutScene(2));
        TextStream::instance() << "You Died.";
    }
}





   /* if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            engine->transitionIntoScene(new GamePlayScene(engine), new FadeOutScene(2));
        }
    } else if(keys & KEY_LEFT) {
        animation->flipHorizontally(true);
    } else if(keys & KEY_RIGHT) {
        animation->flipHorizontally(false);
    } else if(keys & KEY_UP) {
        animation->flipVertically(true);
    } else if(keys & KEY_DOWN) {
        animation->flipVertically(false);
    }*/

