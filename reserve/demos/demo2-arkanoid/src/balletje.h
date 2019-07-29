//
// Created by 11401165 on 26/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALLETJE_H
#define GBA_SPRITE_ENGINE_PROJECT_BALLETJE_H




#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>

class Balletje {
private:
    std::unique_ptr<Sprite> sprite;
    VECTOR dest;
    VECTOR vel;
    int number;
    int dx;
    int dy;


public:
    Balletje(std::unique_ptr<Sprite> sprite, int number, int dx, int dy) : sprite(std::move(sprite)), number(number), dx(dx), dy(dy)  {}
    //ball(int x, int y,int number,int dx, int dy) : x(x), y(y), number(number), size(number*10), dx(dx), dy(dy) { }

    void tick();
    //void setDestination(VECTOR vec);
    //bool isOffScreen() { return sprite->isOffScreen(); }
    Sprite* getSprite() { return sprite.get(); }
};






#endif //GBA_SPRITE_ENGINE_PROJECT_BALLETJE_H
