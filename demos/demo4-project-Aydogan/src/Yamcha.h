//
// Created by aydoganmusa on 30.12.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_YAMCHA_H
#define GBA_SPRITE_ENGINE_PROJECT_YAMCHA_H

#include <libgba-sprite-engine/gba/tonc_math.h>
#include <libgba-sprite-engine/sprites/sprite.h>


class Yamcha {

private:
    std::unique_ptr<Sprite> yamcha;
    bool hurt = false;

public:
    Yamcha(std::unique_ptr<Sprite> sprite) : yamcha(std::move(sprite)) {};

    void gotHurt();

    void notGotHurt();

    void tick();

    Sprite *getSprite() { return yamcha.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_YAMCHA_H
