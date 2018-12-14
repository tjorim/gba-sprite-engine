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
            player.get()
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

    SpriteBuilder<AffineSprite> affineBuilder;

    player = affineBuilder
            .withData(Sonic_sprites_32_32Tiles, sizeof(Sonic_sprites_32_32Tiles))
            .withSize(SIZE_32_32)
            .withAnimated(4,10)
            .withLocation(GBA_SCREEN_WIDTH - 200, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();




    player->stopAnimating();
    TextStream::instance() << "level 1" << "intro";
    //TextStream::instance().setText("x:" + std::to_string(player->getX()), 3, 8);
    //TextStream::instance().setText("y:" + std::to_string(player->getX()), 4, 8);


}

bool runningState = false;
bool isBall = false;
int ballspeed = 1;
void SceneLevel1::tick(u16 keys) {

    TextStream::instance().setText("x:" + std::to_string(player->getX()), 2, 2);
    TextStream::instance().setText("y:" + std::to_string(player->getY()), 3, 2);

    TextStream::instance().setText("scrollY:" + std::to_string(scrollY), 4, 2);


    if(!(keys & KEY_LEFT) && !(keys & KEY_RIGHT)){
        player->stopAnimating();
        player->animateToFrame(4);
        runningState = false;
        TextStream::instance().setText("IDLE", 6, 2);
    }
    else{
        TextStream::instance().setText("ACTIVE", 6, 2);
        if(keys & KEY_RIGHT){
            if(player->getVelocity().y == 0)  //setvelocity  ;
                if(!runningState && !isBall) {
                    player->makeAnimated(6,5,6); //makeAnimated(frames,delay,Startframe)
                    runningState = true;
                    TextStream::instance().setText("RIGHT", 5, 2);
                }
            if(isBall) scrollX += ballspeed;
            bg->scroll(scrollX++ ,scrollY); // als isball = false --> gewoon 1 stap
        }

        if(keys & KEY_LEFT){
            if(player->getVelocity().y == 0)  //setvelocity  ;
                if(!runningState && !isBall) {
                    player->makeAnimated(6,5,14);
                    runningState = true;
                    TextStream::instance().setText("LEFT", 5, 2);

                }
            if(isBall) scrollX -= ballspeed;
            bg->scroll(scrollX--,scrollY);
        }

    }







    if(keys & KEY_UP){
        if(player->getY() == GBA_SCREEN_HEIGHT - 60){
            player->setVelocity(0,-3);
            TextStream::instance().setText("JUMP", 5, 2);

        }
    }


    if(keys & KEY_DOWN){
        if(!isBall) {
            isBall = true;
            player->makeAnimated(4,5,0); //makeAnimated(frames,delay,Startframe)
            TextStream::instance().setText("BALL", 5, 2);
        }
    }

    if(!runningState) isBall = false;

/*
    if(keys & KEY_UP){
        if(player->getY() == GBA_SCREEN_HEIGHT/2) player->setVelocity(0,-1);
        player->animateToFrame(0);
    }


    else{
        if(player->getY() == GBA_SCREEN_HEIGHT/2) {
            player->setVelocity(0, 0);
            if(!(keys & KEY_RIGHT)) player->animateToFrame(0);
        }
    }
    */
    if(player->getY() <= GBA_SCREEN_HEIGHT - 110) player->setVelocity(0,3);
    if(player->getY() == GBA_SCREEN_HEIGHT - 60 && player->getVelocity().y == 3){
        player->setVelocity(0,0);
        TextStream::instance().setText("RESET JUMP", 5, 2);
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

