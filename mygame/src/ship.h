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

public:
    Ship(std::unique_ptr<AffineSprite> s): shipSprite(std::move(s)), dead(false) {}
    Ship(){}
    std::unique_ptr<AffineSprite>& getShipSprite();
    bool isDead() const {return dead;};
    void tick(u16 keys);

};

#endif //GBA_SPRITE_ENGINE_PROJECT_SHIP_H

