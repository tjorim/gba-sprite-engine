//
// Created by Florian on 27/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Victory.h"
#include "StartScene.h"

std::vector<Background *> Victory::backgrounds() {

    return {

    };
}

std::vector<Sprite *> Victory::sprites() {
    return { };
}

void Victory::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("VICTORY !", 6, 12);
}

void Victory::tick(u16 keys) {
    if( keys & KEY_START){
        if(!engine->isTransitioning()){
            engine->transitionIntoScene(new StartScene(engine), new FadeOutScene(2));
        }
    }

}