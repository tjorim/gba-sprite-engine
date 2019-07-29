

#include <libgba-sprite-engine/gba_engine.h>
#include "StartScene.h"



//
// Created by Florian on 29/11/2018.
//
int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    StartScene* startScene = new StartScene(engine);
    engine->setScene(startScene);
     while(true) {
         engine->update();
         engine->delay(1000);
     }
     return 0;
}