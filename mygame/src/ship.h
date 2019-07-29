//
// Created by Ruben Ponsaers on 2/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SHIP_H
#define GBA_SPRITE_ENGINE_PROJECT_SHIP_H

#include <libgba-sprite-engine/gba_engine.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Ship{
private:
    std::unique_ptr<AffineSprite> shipSprite;
    bool dead;
    int speed;

public:
    Ship(std::unique_ptr<AffineSprite> s): shipSprite(std::move(s)), dead(false), speed(1){}
    std::unique_ptr<AffineSprite>& getShipSprite();
    int getSpeed(){ return speed;}
    void explode();
    void tick(u16 keys);
    void setSpeed(int i);

};

#endif //GBA_SPRITE_ENGINE_PROJECT_SHIP_H

