//
// Created by joost on 6/12/2018.
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
#include "scene_level1.h"
#include "scene_level2.h"

std::vector<Sprite *> SceneLevel1::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(player.get());
    sprites.push_back(spikeBall.get());
    sprites.push_back(portal.get());
    //if(!enemyDEAD)sprites.push_back(enemy.get());//voorbeeld om enemy sprite te verwijderen

    return sprites;
}

std::vector<Background *> SceneLevel1::backgrounds() {
    return {
            bg.get()
    };
}

void SceneLevel1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedSonicPalTest, sizeof(sharedSonicPalTest)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(BackgroundLevel1Pal, sizeof(BackgroundLevel1Pal)));

    bg = std::unique_ptr<Background>(new Background(1, BackgroundLevel1Tiles, sizeof(BackgroundLevel1Tiles), map_level1, sizeof(map_level1)));
    bg->useMapScreenBlock(16);

    bg->scroll(scrollX,scrollY);

    engine->setNullptrAsCurrentEffectForTransistion(); //currentEffectForTransition terug nullptr maken om te zorgen dat het mogelijk is om de scene opnieuw te laden als je dood bent. want anders geeft !engine->isTransitioning() na 1 keer altijd true.

    SpriteBuilder<Player> affineBuilder;
    player = affineBuilder
            .withData(Sonic_sprites_32_32TilesTest, sizeof(Sonic_sprites_32_32TilesTest))
            .withSize(SIZE_32_32)
            .withAnimated(4,10)
            .withLocation(GBA_SCREEN_WIDTH - 200, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();

    spikeBall = affineBuilder
            .withData(spikeBallTilesTest, sizeof(spikeBallTilesTest))
            .withSize(SIZE_32_32)
            .withLocation(spikeBallSpawn, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();

    //Zodra portal wordt toegevoegd wordt alles vertraagd.
    portal = affineBuilder// nog toevoegen dat het op de zelfde plaatse staat
            .withData(portal_32_32TilesTest, sizeof(portal_32_32TilesTest))
            .withSize(SIZE_32_32)
            .withAnimated(3,5)
            .withLocation(portalLocation, GBA_SCREEN_HEIGHT - 60)
            .buildPtr();

    player->stopAnimating();
    player->setRunningsState(false);
    TextStream::instance().clear();
    TextStream::instance() << "level 1" << "intro";
    TextStream::instance().setFontColor(0x080F);
    //TextStream::instance().setText("x:" + std::to_string(player->getX()), 3, 8);
    //TextStream::instance().setText("y:" + std::to_string(player->getX()), 4, 8);
}

Timer hitTimer;

void SceneLevel1::tick(u16 keys) {
    hitTimer.onvblank();// geeft ticks aan timer maar timer gaat pas vooruit wanneer timer.start();
    TextStream::instance().setText("HP : " + std::to_string(player->getAmtLives()), 17, 1);

//TextStream for DEBUGGING!!
    //TextStream::instance().setText("x:" + std::to_string(player->getX()), 2, 1);
    //TextStream::instance().setText("y:" + std::to_string(player->getY()), 2, 1);
    //TextStream::instance().setText("spikeball spawn : " + std::to_string(spikeBallSpawn), 2, 1);
    TextStream::instance().setText("Distance to portal: " + std::to_string(-scrollX + portalLocation), 2, 1);

    TextStream::instance().setText("scrollX:" + std::to_string(scrollX), 4, 1);
    //TextStream::instance().setText("Timer:" + std::to_string(timer.getSecs()), 4, 1);
    if(player->collidesWith(*spikeBall)) TextStream::instance().setText("collision", 3, 1);
    else  TextStream::instance().setText("no collision", 3, 1);

    //if(canTakeDamage) TextStream::instance().setText("can Take Damage!!!!!!!!", 4, 1);
    //if(!canTakeDamage) TextStream::instance().setText("can not TakeDamage", 4, 1);

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

    //KEY_A is om manueel de damage te testen
    if((keys & KEY_A && player->getCanTakeDamage()) || (player->collidesWith(*spikeBall) && player->getCanTakeDamage())){ //HIT DETECTION met timer anders gaat HP veel te snel omlaag
        player->setAmtLives(player->getAmtLives()-1);
        hitTimer.start();
        player->setCanTakeDamage(false);
    }
    if(hitTimer.getSecs() >= 2){
        hitTimer.reset();
        player->setCanTakeDamage(true);
    }

    if(!player->getRunnigsState()) player->setIsBall(false);

    if(player->getY() <= GBA_SCREEN_HEIGHT - 110) player->setVelocity(0,3);
    if(player->getY() == GBA_SCREEN_HEIGHT - 60 && player->getVelocity().y == 3){
        player->setVelocity(0,0);
        TextStream::instance().setText("RESET JUMP", 5, 2);
    }

    if(player->getAmtLives() == 0 && !engine->isTransitioning()){
        engine->transitionIntoScene(new SceneLevel1(engine), new FadeOutScene(2));
        TextStream::instance().clear();
        TextStream::instance() << "You Died.";
    }

    if(spikeBall->getY() >= GBA_SCREEN_HEIGHT - 60)spikeBall->setVelocity(0,-1);
    if(spikeBall->getY() <= GBA_SCREEN_HEIGHT - 120)spikeBall->setVelocity(0,1);
    if(spikeBall->isOffScreen() && scrollX > 0 && amtSpikeBallSpawns < 3){
        spikeBallSpawn += 240;
        amtSpikeBallSpawns++;
    }

    spikeBall->moveTo(-scrollX + spikeBallSpawn, spikeBall->getY()); //laat spike ball op een vaste positie staan
    portal->moveTo(-scrollX + portalLocation, portal->getY()); //laat spike ball op een vaste positie staan

    if(player->collidesWith(*portal) && !engine->isTransitioning()){
        engine->transitionIntoScene(new SceneLevel2(engine), new FadeOutScene(2));
        TextStream::instance().clear();
        TextStream::instance() << "Next Level.";
    }
}