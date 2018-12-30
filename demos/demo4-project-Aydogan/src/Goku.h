//
// Created by aydoganmusa on 29.12.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GOKU_H
#define GBA_SPRITE_ENGINE_PROJECT_GOKU_H

#include <libgba-sprite-engine/gba/tonc_math.h>
#include <libgba-sprite-engine/sprites/sprite.h>


class Goku {

private:
    std::unique_ptr<Sprite> goku;
    bool moveLeft = false;
    bool moveRight = false;
    bool kick = false;
    bool hit = false;
    bool omkeren = false;

public:
    Goku(std::unique_ptr<Sprite> sprite) : goku(std::move(sprite)) {};

    void doMoveLeft();

    void doNotMoveLeft();

    void doMoveRight();

    void doNotMoveRight();

    void doKick();

    void doNotKick();

    void doHit();

    void doNotHit();

    void tick();

    Sprite *getSprite() { return goku.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GOKU_H
