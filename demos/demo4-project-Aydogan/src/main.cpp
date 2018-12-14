//
// Created by aydoganmusa on 21.11.18.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "start_scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    StartScene* scene = new StartScene(engine);
    engine->setScene(scene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}