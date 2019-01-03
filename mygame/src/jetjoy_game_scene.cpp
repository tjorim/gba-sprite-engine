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
#include "ship.h"
#include "ghost.h"
#include "jetjoy_dead_scene.h"

JetjoyGameScene::JetjoyGameScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> JetjoyGameScene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(ship->getShipSprite().get());
    sprites.push_back(ghost->getGhostSprite().get());
    sprites.push_back(laser.get());
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

    laser = affineBuilder
            .withData(laserTiles, sizeof(laserTiles))
            .withSize(SIZE_8_8)
            .withLocation(0,0)
            .buildPtr();
    laser->setStayWithinBounds(false);

}

void JetjoyGameScene::tick(u16 keys) {
    ship->tick(keys);
    ghost->tick(keys);


    if(ship->getShipSprite()->collidesWith(*ghost->getGhostSprite())){
        ship->explode();
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            background->clearData();
            engine->transitionIntoScene(new JetjoyDeadScene(engine), new FadeOutScene(2));
        }
    }

    //kill ghost
    if(ghost->getGhostSprite()->collidesWith(*laser)){
        ghost->explode();
        engine->getTimer()->start();

    }

    //revive ghost
    if(engine->getTimer()->getSecs()==3){
        ghost->revive();
        engine->getTimer()->stop();
        engine->getTimer()->reset();
    }

    if(laser->isOffScreen()){
        laser->moveTo(0,0);
        laser->setVelocity(0,0);
    }

    if(keys&KEY_A){
        if((laser->getX()==0)&(laser->getY()==0)){
            laser->moveTo(ship->getShipSprite()->getCenter());
            laser->setVelocity(2,0);
        }
    }


}