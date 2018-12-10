//
// Created by joost on 6/12/2018.
//

#include "game_play_scene.h"

//
// Created by Wouter Groeneveld on 28/07/18.
//

#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Sonic_sprites.h"
#include "game_play_scene.h"

std::vector<Sprite *> GamePlayScene::sprites() {
    return {
            player.get()
    };
}

std::vector<Background *> GamePlayScene::backgrounds() {
    return {
            //bg.get()
    };
}

void GamePlayScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(Sonic_spritesPal, sizeof(Sonic_spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<AffineSprite> affineBuilder;

    player = affineBuilder
            .withData(Sonic_spritesTiles, sizeof(Sonic_spritesTiles))
            .withSize(SIZE_32_64)
            .withAnimated(8,50)
            .withLocation(GBA_SCREEN_WIDTH/2, GBA_SCREEN_HEIGHT/2)
            .buildPtr();

    TextStream::instance() << "level 1" << "intro";

    //bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    //bg.get()->useMapScreenBlock(16);
}

void GamePlayScene::tick(u16 keys) {
   /* if(keys & KEY_START) {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            engine->transitionIntoScene(new GamePlayScene(engine), new FadeOutScene(2));
        }
    } else if(keys & KEY_LEFT) {
        animation->flipHorizontally(true);
    } else if(keys & KEY_RIGHT) {
        animation->flipHorizontally(false);
    } else if(keys & KEY_UP) {
        animation->flipVertically(true);
    } else if(keys & KEY_DOWN) {
        animation->flipVertically(false);
    }*/
}
