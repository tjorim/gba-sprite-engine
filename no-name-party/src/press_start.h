//
// Created by tiele on 8/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
#define GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../sprites/foreground/press_start_left_single.h"
#include "../sprites/foreground/press_start_right_single.h"

class PressStart {
private:
    std::unique_ptr<Sprite> press_start_left, press_start_right;

public:
    PressStart() {
        SpriteBuilder<Sprite> builder;

        press_start_left = std::move(builder.withData(press_start_left_singleTiles,
                                                          sizeof(press_start_left_singleTiles))
                                                .withSize(SIZE_64_32)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 64, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());

        press_start_right = std::move(builder.withData(press_start_right_singleTiles,
                                                         sizeof(press_start_right_singleTiles))
                                                .withSize(SIZE_64_32)
                                                .withLocation(GBA_SCREEN_WIDTH / 2, GBA_SCREEN_HEIGHT - 32)
                                                .buildPtr());
    }

    Sprite *getSpriteLeft() { return press_start_left.get(); }
    Sprite *getSpriteRight() { return press_start_right.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PRESS_START_H
