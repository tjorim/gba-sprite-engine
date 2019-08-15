//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DINO_H
#define GBA_SPRITE_ENGINE_PROJECT_DINO_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "foreground/sprites/bullet_bill_right.h"

class Dino {
private:
    std::unique_ptr<Sprite> sprite;

    int xCo = GBA_SCREEN_WIDTH / 2, yCo = 0;

public:
    Dino() {
        SpriteBuilder<Sprite> builder;

        setSprite(builder.withData(bullet_bill_rightTiles, sizeof(bullet_bill_rightTiles))
                            .withSize(SIZE_32_16)
                            .withAnimated(2, 6)
                            .withLocation(xCo, yCo)
                            .buildPtr());
    }

    int getXCo() const {
        return xCo;
    }

    void setXCo(int xCo) {
        Dino::xCo = xCo;
    }

    int getYCo() const {
        return yCo;
    }

    void setYCo(int yCo) {
        Dino::yCo = yCo;
    }

    Sprite *getDinoSprite() {
        return sprite.get();
    }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Dino::sprite = std::move(sprite);
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOOK_H
