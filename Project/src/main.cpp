
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "start_screen.h"


int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    start_screen* scene = new start_screen(engine);
    engine->setScene(scene);

    while (true) {
        engine->update();
    }

}