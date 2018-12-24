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
#include "Portal_music.h"
#include "Portal_gun_sound.h"
#include "StartSceneSprites.h"


std::vector<Sprite *> Start_scene::sprites() {
    return {chell.get(), portal.get(), portalIn.get(), portalOut.get()};
}

std::vector<Background *> Start_scene::backgrounds() {
    return {bg.get()};
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

    portal = builder
            .withData(Vertical_blue_portalTiles, sizeof(Vertical_blue_portalTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(50,50)
            .buildPtr();

    portalIn = builder
            .withData(Portal_inTiles, sizeof(Portal_inTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(50,50)
            .buildPtr();

    portalOut = builder
            .withData(Portal_outTiles, sizeof(Portal_outTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(50,50)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

}

void Start_scene::tick(u16 keys) {


    }

