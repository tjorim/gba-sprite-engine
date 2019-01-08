//
// Created by mathi on 7/01/2019.
//

#include "Koopa.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29


std::unique_ptr<AffineSprite>& Koopa::getKoopaSprite()  {
    return koopaSprite;
}

bool Koopa::isDead() {
    return dead;
}

void Koopa::kill() {
    dead = true;
}

void Koopa::resurrect() {
    randomTimer = rand() %100 + 150;
}

void Koopa::tick(u16 keys) {
    koopaSprite->setVelocity(-1,0);

    if(keys & KEY_RIGHT){
        koopaSprite->setVelocity(koopaSprite->getVelocity().x-1,0);
    }

    if(koopaSprite->getX() <= 1) koopaSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor32);

    if(randomTimer > 0){
        if(randomTimer == 1){
            dead = false;
            koopaSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor32);
            koopaSprite->animate();
        }
        randomTimer--;
    }
}