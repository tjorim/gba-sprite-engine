//
// Created by tiele on 8/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CLOUD_H
#define GBA_SPRITE_ENGINE_PROJECT_CLOUD_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../sprites/foreground/cloud_left.h"
#include "../sprites/foreground/cloud_right.h"

class Cloud {
private:
    std::unique_ptr<Sprite> cloud_left, cloud_right;

    int yCo = GBA_SCREEN_WIDTH;
    int wind = 0, offset = 0;

public:
    Cloud(int yCo, int wind, int offset) : yCo(yCo), wind(wind), offset(offset) {
        SpriteBuilder<Sprite> builder;

        cloud_left = std::move(builder.withData(cloud_leftTiles, sizeof(cloud_leftTiles))
                                       .withSize(SIZE_64_64)
                                       .withLocation(offset - 128, yCo)
                                       .withVelocity(wind, 0)
                                       .buildPtr());

        cloud_right = std::move(builder.withData(cloud_rightTiles, sizeof(cloud_rightTiles))
                                        .withSize(SIZE_64_64)
                                        .withLocation(offset - 64, yCo)
                                        .withVelocity(wind, 0)
                                        .buildPtr());
    }

    Sprite *getSpriteLeft() { return cloud_left.get(); }

    Sprite *getSpriteRight() { return cloud_right.get(); }

    void setHeight(int yCo) {
        cloud_left->moveTo(cloud_left->getX(), yCo);
        cloud_right->moveTo(cloud_right->getX(), yCo);
    }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_CLOUD_H
