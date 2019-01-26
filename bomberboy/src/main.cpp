#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>
#include <libgba-sprite-engine/gba/tonc_core.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "sound.h"
#include "test_scene.h"

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    TestScene* scene = new TestScene(engine);

    engine->setScene(scene);

    while (true) {
        engine->update();
    }

    return 0;
}