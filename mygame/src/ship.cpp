//
// Created by Ruben Ponsaers on 2/01/2019.
//

#include "ship.h"

std::unique_ptr<AffineSprite>& Ship::getShipSprite() {
    return shipSprite;
}

void Ship::tick(u16 keys) {
    if (!dead) {
        int dx = 0;
        int dy = 0;

        if (!keys) {
            shipSprite->animateToFrame(0);
            shipSprite->setVelocity(0, 0);
        }
        if (keys & KEY_DOWN) {
            dy = 1;
            shipSprite->animateToFrame(2);
            shipSprite->setVelocity(dx, dy);
        } else if (keys & KEY_UP) {
            dy = -1;
            shipSprite->animateToFrame(1);
            shipSprite->setVelocity(dx, dy);
        }
        if (keys & KEY_RIGHT) {
            dx = 1;
            shipSprite->setVelocity(dx, dy);
        } else if (keys & KEY_LEFT) {
            dx = -1;
            shipSprite->setVelocity(dx, dy);
        }
    }
}

void Ship::explode() {
    dead = true;
    shipSprite->setVelocity(0,0);
    shipSprite->animateToFrame(3);
}





