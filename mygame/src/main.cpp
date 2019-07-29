//
// Created by Ruben Ponsaers on 30/11/2018.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "jetjoy_start_scene.h"

int main(){
    std::shared_ptr<GBAEngine> engine (new GBAEngine());

    auto scene = new JetjoyStartScene(engine);
    engine -> setScene(scene);

    while (true){
        engine -> update();
    }
    return 0;
}