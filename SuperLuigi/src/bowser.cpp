//
// Created by mathi on 27/01/2019.
//
#define bottomHeightFor32 45
#define bottomHeightFor16 29

#include "bowser.h"
std::unique_ptr<AffineSprite>& bowser::getBowserSprite() {
    return bowserSprite;
}

void bowser::kill() {
    dead = true;
}

bool bowser::isDead() {
    return dead;
}

void bowser::timer() {
    randomTimer = rand() %100 + 150;
}

int bowser::getTimer() {
    return randomTimer;
}

void bowser::tick(u16 keys) {
   if(!isDead()) {
     if(bowserSprite->getVelocity().y == -1 && bowserSprite ->getVelocity().x == 0) bowserSprite->setVelocity( -1,-1);
     else if( ((bowserSprite->getY() == GBA_SCREEN_HEIGHT-120 && bowserSprite->getVelocity().y < 0)
                 || (bowserSprite->getY() < GBA_SCREEN_HEIGHT-bottomHeightFor32 && bowserSprite->getVelocity().y == 0))) bowserSprite->setVelocity(-1,1);

     else if(bowserSprite->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) bowserSprite ->setVelocity(-1,0);

     if(bowserSprite->getX() <= 1) bowserSprite->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor32);

     if (randomTimer > 0) {
           if (randomTimer == 1) {
               dead = false;
             if(bowserSprite->getY() ==GBA_SCREEN_HEIGHT-bottomHeightFor32) bowserSprite->setVelocity(0,-1);
             timer();
           }
           randomTimer--;

       }
   }
}
