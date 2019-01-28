//
// Created by ubuntu on 29.11.18.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "BetterScene.h"


int main() {
    std::shared_ptr <GBAEngine> engine(new GBAEngine());

    BetterScene *startScene = new BetterScene(engine);
    engine->setScene(startScene);

    while (true) {
        engine->update();
        //engine->delay(1000);
    }

    return 0;
}
