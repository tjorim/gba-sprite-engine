#include <libgba-sprite-engine/gba_engine.h>

/*
#include <libgba-sprite-engine/allocator.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
 */

#include "start_scene/start_scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    StartScene *startScene = new StartScene(engine);
    engine->setScene(startScene);

    while (true) {
        engine->update();
        engine->delay(1000);
    }

    return 0;
}