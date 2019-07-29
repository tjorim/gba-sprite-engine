//
// Created by Ruben Ponsaers on 4/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LASER_H
#define GBA_SPRITE_ENGINE_PROJECT_LASER_H

#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Laser{
private:
    std::unique_ptr<AffineSprite> laserSprite;

public:
    Laser(std::unique_ptr<AffineSprite> s): laserSprite(std::move(s)){}
    std::unique_ptr<AffineSprite>& getLaserSprite();
    void tick(u16 keys);
    void toAmmunition();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_LASER_H
