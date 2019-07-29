//
// Created by 11401165 on 29/11/2018.
//

//
// Created by 11401165 on 29/11/2018.
//



#include <libgba-sprite-engine/gba_engine.h>
#include "SceneLevel1.h"


int main (){

    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    SceneLevel1* startScene = new SceneLevel1(engine);
    engine->setScene(startScene);

    while (true) {
       engine->update();
       engine->delay(1000);
    }

    return 0;

}