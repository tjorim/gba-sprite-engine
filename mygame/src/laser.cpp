//
// Created by Ruben Ponsaers on 4/01/2019.
//

#include "laser.h"

std::unique_ptr<AffineSprite>& Laser::getLaserSprite() {
    return laserSprite;
}

void Laser::tick(u16 keys) {
    if(laserSprite->isOffScreen()){
        toAmmunition();
    }
}

void Laser::toAmmunition() {
    laserSprite->moveTo(0,0);
    laserSprite->setVelocity(0,0);
}