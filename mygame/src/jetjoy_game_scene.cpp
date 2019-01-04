//
// Created by Ruben Ponsaers on 30/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>


#include "jetjoy_game_scene.h"
#include "z_background.h"
#include "z_sharedpal.h"
#include "z_ghost.h"
#include "z_ship.h"
#include "z_laser.h"
#include "y_pats.h"
#include "y_dead.h"
#include "ship.h"
#include "ghost.h"
#include "jetjoy_dead_scene.h"
#include "y_soundstart.h"

JetjoyGameScene::JetjoyGameScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> JetjoyGameScene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(ship->getShipSprite().get());
    sprites.push_back(ghost->getGhostSprite().get());
    sprites.push_back(laser->getLaserSprite().get());
    return sprites;
}

std::vector<Background *> JetjoyGameScene::backgrounds() {
    return {
        background.get()
    };
}

void JetjoyGameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));

    background = std::unique_ptr<Background>(new Background(0, backgroundTiles, sizeof(backgroundTiles), backgroundMap, sizeof(backgroundMap)));
    background.get()->useMapScreenBlock(16);

    SpriteBuilder<AffineSprite> affineBuilder;

    shipSprite = affineBuilder
            .withData(shipTiles, sizeof(shipTiles))
            .withSize(SIZE_32_32)
            .withinBounds()
            .withLocation(10,80)
            .buildPtr();
    ship = std::unique_ptr<Ship>(new Ship(std::move(shipSprite)));

    ghostSprite = affineBuilder
            .withData(ghostTiles, sizeof(ghostTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT - 40)
            .buildPtr();
    ghostSprite->setStayWithinBounds(false);
    ghost = std::unique_ptr<Ghost>(new Ghost(std::move(ghostSprite)));

    laserSprite = affineBuilder
            .withData(laserTiles, sizeof(laserTiles))
            .withSize(SIZE_8_8)
            .withLocation(0,0)
            .buildPtr();
    laserSprite->setStayWithinBounds(false);
    laser = std::unique_ptr<Laser>(new Laser(std::move(laserSprite)));

    score=0;
    nextlevel= false;

}

void JetjoyGameScene::tick(u16 keys) {
    ship->tick(keys);
    ghost->tick(keys);
    laser->tick(keys);
    scoreHandler();

    //kill ship
    if(ship->getShipSprite()->shipCollide(*ghost->getGhostSprite())){
        ship->explode();
        ghost->getGhostSprite()->moveTo(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT);
        endgame();
    }

    //kill ghost
    if(ghost->getGhostSprite()->collidesWith(*laser->getLaserSprite())){
        ghost->explode();
        if((score==2)||score==5){nextlevel=true;}
        laser->toAmmunition();
        engine.get()->enqueueSound(raw_pats, sizeof(raw_pats), 32000);
        engine->getTimer()->start();

    }

    //revive ghost
    if(engine->getTimer()->getSecs()==3){
        ghost->revive();
        score++;
        if((score==3)||score==6){nextlevel=false;}
        ghost->incrementSpeed();
        engine->getTimer()->stop();
        engine->getTimer()->reset();


    }

    if(keys&KEY_A){
        if((laser->getLaserSprite()->getX()==0)&(laser->getLaserSprite()->getY()==0)){
            laser->getLaserSprite()->moveTo(ship->getShipSprite()->getCenter());
            laser->getLaserSprite()->setVelocity(ship->getSpeed()*2,0);
        }
    }

    if(nextlevel) {
        engine.get()->enqueueSound(raw_nextlevel, sizeof(raw_nextlevel), 32000);
    }
}

void JetjoyGameScene::endgame() {
    engine.get()->enqueueSound(raw_dead, sizeof(raw_dead), 32000);
    engine->stopTransitioning();
    if (!engine->isTransitioning()) {
        background->clearData();
        engine->transitionIntoScene(new JetjoyDeadScene(engine, score), new FadeOutScene(2));
    }
}

void JetjoyGameScene::scoreHandler() {
    if(score==3){
        ship->setSpeed(2);
    }
    else if(score==6){
        ship->setSpeed(3);
    }
}