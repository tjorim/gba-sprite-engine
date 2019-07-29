//
// Created by 11401165 on 30/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALL_H
#define GBA_SPRITE_ENGINE_PROJECT_BALL_H


#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>

class Ball {
private:
    std::unique_ptr<Sprite> sprite;
    VECTOR vel;
    int number;
    int dx;
    int dy;
public:
    Ball(std::unique_ptr<Sprite> sprite, int number, int dx, int dy) : sprite(std::move(sprite)), number(number), dx(dx), dy(dy)  {}
    void tick();
    void setDx(int dx_new){ dx = dx_new;};
    Sprite* getSprite() { return sprite.get(); }
    int getNumber() {return number;}

};
#endif //GBA_SPRITE_ENGINE_PROJECT_BALL_H
