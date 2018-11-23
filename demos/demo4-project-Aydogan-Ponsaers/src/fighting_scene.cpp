//
// Created by aydoganmusa on 22.11.18.
//


#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "fighting_scene.h"
#include "goku.h"


std::vector<Sprite *> FightingScene::sprites() {
    return {
        goku.get()
    };
}

std::vector<Background *> FightingScene::backgrounds() {
    return {};
}

void FightingScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(goku_palette, sizeof(goku_palette)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());
    SpriteBuilder<Sprite> Builder;

    goku = Builder
            .withData(goku_data, sizeof(goku_data))
            .withSize(SIZE_32_32)
            .withAnimated(3, 3)
            .withLocation(32, GBA_SCREEN_HEIGHT / 2 - 32)
            .withinBounds()
            .buildPtr();
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
