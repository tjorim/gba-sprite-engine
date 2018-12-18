//
// Created by Leander on 16/12/2018.
//

#include "Start_scene.h"
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level_scene.h"
#include "Level1_background.h"
#include "Scene_sprites.h"
#include "Portal_music.h"
#include "Portal_gun_sound.h"

/*
std::vector<Sprite *> Start_scene::sprites() {

    return {sprites};
}

std::vector<Background *> Start_scene::backgrounds() {
    return {
            bg.get()
    };
}


void Start_scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;

    chell = builder
            .withData(chellTiles, sizeof(chellTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(50,50)
            .buildPtr();



    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    //engine->enqueueMusic(Still_Alive, 1412466, 88200);
}

void Start_scene::tick(u16 keys) {


    }

*/