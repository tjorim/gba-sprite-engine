//
// Created by Ruben on 27/01/2019.
//

#include "Bullet.h"

void Bullet::updateSprite() {
    getView()->setVelocity(_vel.GetX(), _vel.GetY());
}
