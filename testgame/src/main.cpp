//
// Created by Jolien Jeunen on 25/01/2019.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "MainScene.h"


/**
 * shared palette extracted from grit
 * ./../grit piskel.png piskel2.png kul.png -ftc -pS -gB8 -O shared.c
 * assumes 8bpp sprites
 */

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    MainScene* startScene = new MainScene(engine);
    engine->setScene(startScene);



    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}