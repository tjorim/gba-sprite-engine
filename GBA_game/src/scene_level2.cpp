//
// Created by Dominique on 20-Jan-19.
//
#include <string>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Sonic_sprites.h"
#include "scene_level2.h"
#include "background_level1.h"

std::vector<Sprite *> SceneLevel2::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(player.get());
    sprites.push_back(portal.get());

    return sprites;
}

std::vector<Background *> SceneLevel2::backgrounds() {
    return {
            bg.get()
    };
}

void SceneLevel2::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedSonicPalTest, sizeof(sharedSonicPalTest)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(BackgroundLevel1Pal, sizeof(BackgroundLevel1Pal)));

    bg = std::unique_ptr<Background>(new Background(1, BackgroundLevel1Tiles, sizeof(BackgroundLevel1Tiles), map_level1, sizeof(map_level1)));
    bg->useMapScreenBlock(16);

    engine->setNullptrAsCurrentEffectForTransistion(); //currentEffectForTransition terug nullptr maken om te zorgen dat het mogelijk is om de scene opnieuw te laden als je dood bent. want anders geeft !engine->isTransitioning() na 1 keer altijd true.

    SpriteBuilder<Player> affineBuilder;
    player = affineBuilder
            .withData(Sonic_sprites_32_32TilesTest, sizeof(Sonic_sprites_32_32TilesTest))
            .withSize(SIZE_32_32)
            .withAnimated(4,10)
            .withLocation(GBA_SCREEN_WIDTH - 200, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();

    player->stopAnimating();
    player->setRunningsState(false);

    portal = affineBuilder
            .withData(portal_32_32TilesTest, sizeof(portal_32_32TilesTest))
            .withSize(SIZE_32_32)
            .withAnimated(3,5)
            .withLocation(portalLocation, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();

    TextStream::instance().clear();
    TextStream::instance() << "level 2" << "boss battle";
    TextStream::instance().setFontColor(0x080F);
}

void SceneLevel2::tick(u16 keys) {
    TextStream::instance().setText("HP : " + std::to_string(player->getAmtLives()), 17, 1);

    if(!(keys & KEY_LEFT) && !(keys & KEY_RIGHT)){
        player->stopAnimating();
        if(player->getDirection() == DirectionRight)player->animateToFrame(4);
        if(player->getDirection() == DirectionLeft)player->animateToFrame(12);
        player->setRunningsState(false);
        TextStream::instance().setText("IDLE", 6, 2);
    }
    else{
        TextStream::instance().setText("ACTIVE", 6, 1);
        if(keys & KEY_RIGHT){
            if(player->getVelocity().y == 0)  //setvelocity  ;
                if(!player->getRunnigsState() && !(player->getIsBall())) {
                    player->makeAnimated(6,5,6); //makeAnimated(frames,delay,Startframe)
                    player->setRunningsState(true);
                    player->setDirection(DirectionRight);
                    TextStream::instance().setText("RIGHT", 5, 1);
                }
            if(player->getIsBall()) scrollX += player->getBallSpeed();
            bg->scroll(scrollX++ ,scrollY); // als isball = false --> gewoon 1 stap
        }

        if(keys & KEY_LEFT){
            if(player->getVelocity().y == 0)  //setvelocity  ;
                if(!player->getRunnigsState() && !(player->getIsBall())) {
                    player->makeAnimated(6,5,14);
                    player->setRunningsState(true);
                    player->setDirection(DirectionLeft);
                    TextStream::instance().setText("LEFT", 5, 1);

                }
            if(player->getIsBall()) scrollX -= player->getBallSpeed();
            bg->scroll(scrollX--,scrollY);
        }

    }

    if(keys & KEY_UP){ // springen --> later in variabelen steken van Player
        if(player->getY() == GBA_SCREEN_HEIGHT - 60){
            player->setVelocity(0,-3);
            TextStream::instance().setText("JUMP", 5, 2);

        }
    }

    if(keys & KEY_DOWN){
        if(!(player->getIsBall())) {
            player->setIsBall(true);
            player->makeAnimated(4,5,0); //makeAnimated(frames,delay,Startframe)
            TextStream::instance().setText("BALL", 5, 2);
        }
    }

    if(!player->getRunnigsState()) player->setIsBall(false);
    if(player->getY() <= GBA_SCREEN_HEIGHT - 110) player->setVelocity(0,3);
    if(player->getY() == GBA_SCREEN_HEIGHT - 60 && player->getVelocity().y == 3){
        player->setVelocity(0,0);
        TextStream::instance().setText("RESET JUMP", 5, 2);
    }

    if(player->getAmtLives() == 0 && !engine->isTransitioning()){
        engine->transitionIntoScene(new SceneLevel2(engine), new FadeOutScene(2));
        TextStream::instance().clear();
        TextStream::instance() << "You Died.";
    }

    portal->moveTo(-scrollX + portalLocation,portal->getY());

    if(player->collidesWith(*portal) && !engine->isTransitioning()){
        engine->transitionIntoScene(new SceneLevel2(engine), new FadeOutScene(2));
        TextStream::instance().clear();
        TextStream::instance() << "Next Level.";
    }
}