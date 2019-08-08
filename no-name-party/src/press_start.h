//
// Created by tiele on 8/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
#define GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../sprites/foreground/press_start_new_1.h"
#include "../sprites/foreground/press_start_new_2.h"
#include "../sprites/foreground/press_start_new_3.h"
#include "../sprites/foreground/press_start_new_4.h"

class PressStart {
private:
    std::unique_ptr<Sprite> press_start_1, press_start_2, press_start_3, press_start_4;

public:
    PressStart() {
        SpriteBuilder<Sprite> builder;

        press_start_1 = std::move(builder.withData(press_start_new_1Tiles,
                                                          sizeof(press_start_new_1Tiles))
                                                .withSize(SIZE_32_16)
                                                .withAnimated(4, 4)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());

        press_start_2 = std::move(builder.withData(press_start_new_2Tiles,
                                                         sizeof(press_start_new_2Tiles))
                                                .withSize(SIZE_32_16)
                                                .withAnimated(4, 4)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());

        press_start_3 = std::move(builder.withData(press_start_new_3Tiles,
                                                          sizeof(press_start_new_3Tiles))
                                                .withSize(SIZE_32_16)
                                                .withAnimated(4, 4)
                                                .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());

        press_start_4 = std::move(builder.withData(press_start_new_4Tiles,
                                                         sizeof(press_start_new_4Tiles))
                                                .withSize(SIZE_32_16)
                                                .withAnimated(4, 4)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 + 32, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());
    }

    Sprite *getSprite1() { return press_start_1.get(); }
    Sprite *getSprite2() { return press_start_2.get(); }
    Sprite *getSprite3() { return press_start_3.get(); }
    Sprite *getSprite4() { return press_start_4.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
