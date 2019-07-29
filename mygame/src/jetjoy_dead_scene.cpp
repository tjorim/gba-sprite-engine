//
// Created by Ruben Ponsaers on 03/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "jetjoy_dead_scene.h"
#include "jetjoy_start_scene.h"

JetjoyDeadScene::JetjoyDeadScene(const std::shared_ptr<GBAEngine> &engine, int score) : Scene(engine), score(score) {}

std::vector<Background *> JetjoyDeadScene::backgrounds() {
    return {};
}

std::vector<Sprite *> JetjoyDeadScene::sprites() {
    return {};
}

void JetjoyDeadScene::load() {
    TextStream::instance().setText("YOU DIED!", 8, 12);
    TextStream::instance().setText("YOU KILLED: " + std::to_string(score) + " SPOOKSKES" , 10, 4);

}

void JetjoyDeadScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            TextStream::instance().clear();
            engine->transitionIntoScene(new JetjoyStartScene(engine), new FadeOutScene(2));

        }
    }
}