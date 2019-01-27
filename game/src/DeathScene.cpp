
#include "DeathScene.h"
#include "StartScene.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "BattleScene_EyeMonster.h"



//
// Created by Florian on 26/01/2019.
//
std::vector<Background *> DeathScene::backgrounds() {

    return {

    };
}

std::vector<Sprite *> DeathScene::sprites() {
    return { };
}

void DeathScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("YOU DIED", 6, 13);
    TextStream::instance().setText("PRESS ENTER", 8, 13);
    TextStream::instance().setText("TO RESTART", 9, 13);
}

void DeathScene::tick(u16 keys) {
    if( keys & KEY_START){
        if(!engine->isTransitioning()){
            engine->transitionIntoScene(new BattleScene_EyeMonster(engine), new FadeOutScene(2));
        }
    }

}