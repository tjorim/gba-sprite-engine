//
// Created by lloyd on 29-Nov-18.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "StartScene.h"
#include "CityScene.h"


int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    StartScene* startScene = new StartScene(engine);
    engine->setScene(startScene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}