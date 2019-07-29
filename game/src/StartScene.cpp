//
// Created by Florian on 29/11/2018.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "StartScene.h"
#include "Background_1.h"
#include "BattleScene_EyeMonster.h"
#include "Victory.h"
#include "Victory_Scene.h"


std::vector<Background *> StartScene::backgrounds() {

    return {

    };
}

std::vector<Sprite *> StartScene::sprites() {
    return { };
}

void StartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("PRESS START", 3, 8);
}

void StartScene::tick(u16 keys) {
    if( keys & KEY_START){
        if(!engine->isTransitioning()){
            engine->transitionIntoScene(new BattleScene_EyeMonster(engine), new FadeOutScene(2));
        }
    }

}