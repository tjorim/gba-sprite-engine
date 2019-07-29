//
// Created by 11401165 on 26/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALL_H
#define GBA_SPRITE_ENGINE_PROJECT_BALL_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>

class Ball {
private:
    std::unique_ptr<Sprite> sprite;
    VECTOR dest;
    VECTOR vel;

public:
    Ball(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)), dest(VECTOR()) {}

    void tick();
    void setDestination(VECTOR vec);
    bool isOffScreen() { return sprite->isOffScreen();
    Sprite* getSprite() { return sprite.get(); }
};



#endif //GBA_SPRITE_ENGINE_PROJECT_BALL_H
