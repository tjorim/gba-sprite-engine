//
// Created by joost on 29/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>


#include "start_scene.h"
#include "background.h"
#include "../../demos/demo1-basicfeatures/src/sample_sound.h"

std::vector<Background *> StartScene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> StartScene::sprites() {
    return {};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));

    //SpriteBuilder<Sprite> builder;
/*
    animation = builder
            .withData(backgroundTiles, sizeof(backgroundTiles[19200]))
            .withSize(SIZE_32_32)
            .withAnimated(6, 3)
            .withLocation(50, 50)
            .buildPtr();

    TextStream::instance().setText("PRESS START", 3, 8);
    engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
*/
    bg = std::unique_ptr<Background>(new Background(1, backgroundTiles, sizeof(backgroundTiles
    ), backgroundMap, sizeof(backgroundMap)));
    bg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {
}
