//
// Created by Leander on 16/12/2018.
//

#include "StartScene.h"
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "Level1_background.h"
#include "LevelScene.h"
#include "Scene_sprites.h"
#include "Portal_gun_sound.h"


std::vector<Sprite *> StartScene::sprites() {
    return {chell.get(), portalOut.get(), portal.get()};
}

std::vector<Background *> StartScene::backgrounds() {
    return {bg.get()};
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;

    chell = builder
            .withData(chellTiles, sizeof(chellTiles))
            .withSize(SIZE_16_32)
            .withLocation(20,112)
            .buildPtr();

    portal = builder
            .withData(Vertical_blue_portalTiles, sizeof(Vertical_blue_portalTiles))
            .withSize(SIZE_8_32)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();


    portalOut = builder
            .withData(Portal_outTiles, sizeof(Portal_outTiles))
            .withSize(SIZE_32_64)
            .withLocation(150,20)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    TextStream::instance().setText(std::string("Portal 2.5"), 5, 8);

}

void StartScene::tick(u16 keys) {
    if (keys && KEY_A){
        chell->makeAnimated(4,6);
        chell->setVelocity(1,0);
        engine->enqueueSound(Portalgun_sound, 18996, 16000);
        portal->moveTo(200,112);
    }
    if(chell->collidesWith(*portal)){
        LevelScene* startScene = new LevelScene(engine);
        engine->transitionIntoScene(startScene, new FadeOutScene(3));
    }

}

