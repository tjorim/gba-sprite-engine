//
// Created by Ruben Ponsaers on 30/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>


#include "jetjoy_game_scene.h"
#include "z_background.h"
#include "z_foreground.h"
#include "ship.h"



std::vector<Sprite *> JetjoyGameScene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(ship->getShipSprite().get());

    return sprites;
}

std::vector<Background *> JetjoyGameScene::backgrounds() {
    return {
        background.get()
    };
}

void JetjoyGameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(shipPal, sizeof(shipPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));

    background = std::unique_ptr<Background>(new Background(1, backgroundTiles, sizeof(backgroundTiles), backgroundMap, sizeof(backgroundMap)));
    background.get()->useMapScreenBlock(16);

    SpriteBuilder<AffineSprite> affineBuilder;

    shipSprite = affineBuilder
            .withData(shipTiles, sizeof(shipTiles))
            .withSize(SIZE_32_32)
            .withinBounds()
            .withLocation(10,80)
            .withAnimated(2,20)
            .buildPtr();

    ship = std::unique_ptr<Ship>(new Ship(std::move(shipSprite)));
    ship->getShipSprite()->stopAnimating();
}

void JetjoyGameScene::tick(u16 keys) {
    ship->tick(keys);
}