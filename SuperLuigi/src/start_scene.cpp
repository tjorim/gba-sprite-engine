//
// Created by Craeghs Mathias on 2/12/2018.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "start_scene.h"
#include "LuigiTiles.h"
#include "level1.h"
#include "end_scene.h"
#include "goombaTiles.h"
#include "sharedPal.h"

std::vector<Background *> start_scene::backgrounds() {
    return {};
}


std::vector<Sprite *> start_scene::sprites() {

    std::vector<Sprite*> sprites;
    sprites.push_back(luigi.get());
    sprites.push_back(goomba.get());

    return { sprites};
}

void start_scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritesPal, sizeof(spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("PRESS START", 3, 8);
    TextStream::instance().setText("In een wereld waar Luigi        jaloers is op Mario. Gaat hij   zelf opzoek naar de             speelervaring!! ",4,0);

    SpriteBuilder<AffineSprite> affineBuilder;

    luigi = affineBuilder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH/2, GBA_SCREEN_HEIGHT/2)
            .withAnimated(5,10)
            .buildPtr();

    goomba = affineBuilder
            .withData(GoombaTiles, sizeof(GoombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH/2 -20 , GBA_SCREEN_HEIGHT/2 +16)
            .withAnimated(3,5)
            .buildPtr();
}

void start_scene::tick(u16 keys) {
    if(keys){
        goomba ->flipHorizontally(true);
    }
    if(keys & KEY_START) {
        if(!engine->isTransitioning()) {

            TextStream::instance() << "entered: starting next scene";

            engine->transitionIntoScene(new level1(engine), new FadeOutScene(2));
        }
    }
}
