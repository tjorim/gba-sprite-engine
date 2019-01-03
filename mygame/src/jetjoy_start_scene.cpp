//
// Created by Ruben Ponsaers on 30/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/gba_engine.h>


#include "jetjoy_start_scene.h"
#include "jetjoy_game_scene.h"

JetjoyStartScene::JetjoyStartScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

std::vector<Background *> JetjoyStartScene::backgrounds() {
    return {};
}

std::vector<Sprite *> JetjoyStartScene::sprites() {
    return {};
}

void JetjoyStartScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("JETJOY", 8, 12);
    TextStream::instance().setText("PRESS START TO BEGIN", 10, 5);
}

void JetjoyStartScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new JetjoyGameScene(engine), new FadeOutScene(2));
        }
    }
}