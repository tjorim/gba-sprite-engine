//
// Created by tiele on 8/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TITLE_H
#define GBA_SPRITE_ENGINE_PROJECT_TITLE_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../sprites/foreground/title_left.h"
#include "../sprites/foreground/title_middle.h"
#include "../sprites/foreground/title_right.h"

class Title {
private:
    std::unique_ptr<Sprite> title_left, title_middle, title_right;

public:
    Title() {
        SpriteBuilder<Sprite> builder;

        title_left = std::move(builder.withData(title_leftTiles,
                                                sizeof(title_leftTiles))
                                       .withSize(SIZE_64_64)
                                       .withLocation(GBA_SCREEN_WIDTH / 2 - 96, 16)
                                       .buildPtr());

        title_middle = std::move(builder.withData(title_middleTiles,
                                                  sizeof(title_middleTiles))
                                         .withSize(SIZE_64_64)
                                         .withLocation(GBA_SCREEN_WIDTH / 2 - 32, 16)
                                         .buildPtr());

        title_right = std::move(builder.withData(title_rightTiles,
                                                 sizeof(title_rightTiles))
                                        .withSize(SIZE_64_64)
                                        .withLocation(GBA_SCREEN_WIDTH / 2 + 32, 16)
                                        .buildPtr());
    }

    Sprite *getSpriteLeft() { return title_left.get(); }

    Sprite *getSpriteMiddle() { return title_middle.get(); }

    Sprite *getSpriteRight() { return title_right.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_TITLE_H
