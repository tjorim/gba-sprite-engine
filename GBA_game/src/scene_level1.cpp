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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(Sonic_spritesPal, sizeof(Sonic_spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(BackgroundLevel1Pal, sizeof(BackgroundLevel1Pal)));

    bg = std::unique_ptr<Background>(new Background(1, BackgroundLevel1Tiles, sizeof(BackgroundLevel1Tiles), map_level1, sizeof(map_level1)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<AffineSprite> affineBuilder;

    player = affineBuilder
            .withData(Sonic_spritesTiles, sizeof(Sonic_spritesTiles))
            .withSize(SIZE_32_64)
            .withAnimated(16,10)
            .withLocation(GBA_SCREEN_WIDTH - 200, GBA_SCREEN_HEIGHT - 100)
            .buildPtr();

    player->stopAnimating();

    TextStream::instance() << "level 1" << "intro";
    TextStream::instance().setText("x:" + std::to_string(player->getX()), 3, 8);
    TextStream::instance().setText("y:" + std::to_string(player->getX()), 4, 8);


}

bool runningState = false;


void SceneLevel1::tick(u16 keys) {

    TextStream::instance().setText("x:" + std::to_string(player->getX()), 3, 2);
    TextStream::instance().setText("y:" + std::to_string(player->getY()), 4, 2);


    if(keys & KEY_RIGHT){
        if(player->getVelocity().y == 0)  //setvelocity  ;
        if(!runningState) {
            player->makeAnimated(6,3,2); //makeAnimated(frames,delay,Startframe)
            runningState = true;
        }
        //scrollX +=1;
        //bg->scroll(scrollX,scrollY);
    }

    if(keys & KEY_LEFT){
        if(player->getVelocity().y == 0)  //setvelocity  ;
            if(!runningState) {
                player->makeAnimated(6,3,10);
                runningState = true;
            }
        //scrollX +=1;
        //bg->scroll(scrollX,scrollY);
    }
    if(!keys){
        player->stopAnimating();
        player->animateToFrame(0);
        runningState = false;
    }


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
    if(player->getY() == GBA_SCREEN_HEIGHT-80) player->setVelocity(0,1);
*/
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

