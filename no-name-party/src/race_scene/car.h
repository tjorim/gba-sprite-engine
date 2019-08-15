//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CAR_H
#define GBA_SPRITE_ENGINE_PROJECT_CAR_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "foreground/sprites/bullet_bill_up.h"

class Car {
private:
    std::unique_ptr<Sprite> sprite;

    int xCo = GBA_SCREEN_WIDTH / 2 - 8, yCo = GBA_SCREEN_HEIGHT - 40;

public:
    Car() {
        SpriteBuilder<Sprite> builder;

        setSprite(builder.withData(bullet_bill_upTiles, sizeof(bullet_bill_upTiles))
                            .withSize(SIZE_16_32)
                            .withAnimated(2, 6)
                            .withLocation(xCo, yCo)
                            .buildPtr());
    }

    void moveToX(int xValue) {
        Car::xCo = xValue;
        sprite->moveTo(xCo, yCo);
    }

    int getXCo() const {
        return xCo;
    }

    void setXCo(int xCo) {
        Car::xCo = xCo;
    }

    int getYCo() const {
        return yCo;
    }

    void setYCo(int yCo) {
        Car::yCo = yCo;
    }

    Sprite *getCarSprite() {
        return sprite.get();
    }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Car::sprite = std::move(sprite);
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOOK_H
