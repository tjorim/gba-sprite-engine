//
// Created by Wout Briels on 29/11/2018.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "Level1Scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    Level1Scene* level1Scene = new Level1Scene(engine);
    engine->setScene(level1Scene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}