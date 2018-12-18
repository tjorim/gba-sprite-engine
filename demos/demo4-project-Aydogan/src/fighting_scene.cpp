//
// Created by aydoganmusa on 22.11.18.
//


#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "fighting_scene.h"


std::vector<Sprite *> FightingScene::sprites() {
    return {
            goku.get(), oozaru.get()
    };
}

std::vector<Background *> FightingScene::backgrounds() {
    return {bg.get()};
}

void FightingScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(wastelandPal, sizeof(wastelandPal)));
    SpriteBuilder<Sprite> Builder;

    goku = Builder
            .withData(gokuTiles, sizeof(gokuTiles))
            .withSize(SIZE_32_32)
            .withAnimated(3, 3)
            .withLocation(16, GBA_SCREEN_HEIGHT / 2 - 32)
            .withinBounds()
            .buildPtr();

    oozaru = Builder
            .withData(oozaruTiles, sizeof(oozaruTiles))
            .withSize(SIZE_32_64)
            .withAnimated(1, 3)
            .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT)
            .withinBounds()
            .buildPtr();

    bg = std::unique_ptr<Background>(
            new Background(0, wastelandTiles, sizeof(wastelandTiles), wastelandMap, sizeof(wastelandMap)));
    bg.get()->useMapScreenBlock(26);


}

void FightingScene::tick(u16 keys) {
    if(keys & KEY_UP){
        goku->setVelocity(0,+2);
    } else if(keys & KEY_DOWN){
        goku->setVelocity(0,-2);
    }else {
        goku->setVelocity(0,0);
    }
}
