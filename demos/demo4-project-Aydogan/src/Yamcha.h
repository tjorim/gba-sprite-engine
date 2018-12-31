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
    std::unique_ptr<Sprite> lifebar;
    bool hurt = false;
    int levenspunten = 300;

public:
    Yamcha(std::unique_ptr<Sprite> sprite1, std::unique_ptr<Sprite> sprite2) : yamcha(std::move(sprite1)),
                                                                               lifebar(std::move(sprite2)) {};

    void gotHurt();

    void notGotHurt();

    void tick();

    Sprite *getSpriteYamcha() { return yamcha.get(); }

    Sprite *getSpriteLifebarYamcha() { return lifebar.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_YAMCHA_H
