//
// Created by Jolien Jeunen on 27/01/2019.
//

#include "StartScene.h"

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "birdstartscherm.h"
#include "MainScene.h"
//#include "flappybirdachtergrond.h"
#include "startschermachtergrondFB.h"
#include "flappybird.h"

std::vector<Background *> StartScene::backgrounds() {
    return { startbg.get()};
}

std::vector<Sprite *> StartScene::sprites() {
    return {  flappyBird.get() };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(birdstartschermPal, sizeof(birdstartschermPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(flappybirdPal, sizeof(flappybirdPal)));

    SpriteBuilder<Sprite> builder;

    flappyBird = builder
            .withData(birdstartschermTiles, sizeof(birdstartschermTiles))
            .withSize(SIZE_32_16)
            .withAnimated(3, 6)
            .withLocation(100, 80)
            .buildPtr();

    TextStream::instance().setText("PRESS START", 4, 9);
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);

    startbg = std::unique_ptr<Background>(new Background(1, flappybirdTiles, sizeof(flappybirdTiles), startschermMAP, sizeof(startschermMAP)));
    startbg.get()->useMapScreenBlock(16);
}

void StartScene::tick(u16 keys) {
    if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            engine->transitionIntoScene(new MainScene(engine), new FadeOutScene(2));
        }
    } else if(keys & KEY_LEFT) {
        flappyBird->flipHorizontally(true);
    } else if(keys & KEY_RIGHT) {
        flappyBird->flipHorizontally(false);
    } else if(keys & KEY_UP) {
        flappyBird->flipVertically(true);
    } else if(keys & KEY_DOWN) {
        flappyBird->flipVertically(false);
    }
}
