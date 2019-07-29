//
// Created by 11401165 on 29/11/2018.
//

//
// Created by 11401165 on 29/11/2018.
//



#include <libgba-sprite-engine/gba_engine.h>
#include "SceneLevel1.h"
#include "Level1.h"
#include "Level2.h"

int main (){

    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    Level1* startScene = new Level1(engine,0);
    //Level2* startScene = new Level2(engine,0);
    engine->setScene(startScene);

    while (true) {
       engine->update();
       engine->delay(1000);
    }

    return 0;

}