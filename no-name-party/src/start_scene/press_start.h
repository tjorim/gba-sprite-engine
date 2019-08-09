//
// Created by tiele on 8/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
#define GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "foreground/sprites/press_start_simple_1.h"
#include "foreground/sprites/press_start_simple_2.h"
#include "foreground/sprites/press_start_simple_3.h"
#include "foreground/sprites/press_start_simple_4.h"

#include "foreground/sprites/press_start_single_1.h"
#include "foreground/sprites/press_start_single_2.h"
#include "foreground/sprites/press_start_single_3.h"
#include "foreground/sprites/press_start_single_4.h"

class PressStart {
private:
    std::unique_ptr<Sprite> press_start_1, press_start_2, press_start_3, press_start_4;

    bool animated = false;

public:
    PressStart(bool animated) : animated(animated) {
        SpriteBuilder<Sprite> builder;

        if (animated) {
            press_start_1 = std::move(builder.withData(press_start_simple_1Tiles,
                                                       sizeof(press_start_simple_1Tiles))
                                              .withSize(SIZE_32_16)
                                              .withAnimated(4, 8)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_2 = std::move(builder.withData(press_start_simple_2Tiles,
                                                       sizeof(press_start_simple_2Tiles))
                                              .withSize(SIZE_32_16)
                                              .withAnimated(4, 8)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_3 = std::move(builder.withData(press_start_simple_3Tiles,
                                                       sizeof(press_start_simple_3Tiles))
                                              .withSize(SIZE_32_16)
                                              .withAnimated(4, 8)
                                              .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_4 = std::move(builder.withData(press_start_simple_4Tiles,
                                                       sizeof(press_start_simple_4Tiles))
                                              .withSize(SIZE_32_16)
                                              .withAnimated(4, 8)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 + 32, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());
        } else {
            press_start_1 = std::move(builder.withData(press_start_single_1Tiles,
                                                       sizeof(press_start_single_1Tiles))
                                              .withSize(SIZE_32_16)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_2 = std::move(builder.withData(press_start_single_2Tiles,
                                                       sizeof(press_start_single_2Tiles))
                                              .withSize(SIZE_32_16)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_3 = std::move(builder.withData(press_start_single_3Tiles,
                                                       sizeof(press_start_single_3Tiles))
                                              .withSize(SIZE_32_16)
                                              .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());

            press_start_4 = std::move(builder.withData(press_start_single_4Tiles,
                                                       sizeof(press_start_single_4Tiles))
                                              .withSize(SIZE_32_16)
                                              .withLocation(GBA_SCREEN_WIDTH / 2 + 32, GBA_SCREEN_HEIGHT - 32)
                                              .buildPtr());
        }
    }

    Sprite *getSprite1() { return press_start_1.get(); }

    Sprite *getSprite2() { return press_start_2.get(); }

    Sprite *getSprite3() { return press_start_3.get(); }

    Sprite *getSprite4() { return press_start_4.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
