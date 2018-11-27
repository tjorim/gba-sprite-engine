//
// Created by Vandebosch Remy on 27/11/2018.
//

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

int main(){
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    //create scene and set to engine
    while(true){
        engine->update();
    }

    return 0;
}