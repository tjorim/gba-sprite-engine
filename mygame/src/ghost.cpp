//
// Created by Ruben Ponsaers on 3/01/2019.
//

#include "ghost.h"

std::unique_ptr<AffineSprite>& Ghost::getGhostSprite() {
    return ghostSprite;
}

void Ghost::tick(u16 keys) {

    if(!dead){
        ghostSprite->setVelocity(-speed,0);

        if(ghostSprite->isOffScreen()){
            ghostSprite->moveTo(GBA_SCREEN_WIDTH,rand() % 140);
        }
    }
}

void Ghost::explode() {
    ghostSprite->animateToFrame(1);
    ghostSprite->setVelocity(0,0);
    dead=true;
}

void Ghost::revive() {
    ghostSprite->animateToFrame(0);
    ghostSprite->moveTo(GBA_SCREEN_WIDTH,rand() % 160);
    dead=false;
}

void Ghost::incrementSpeed(){
    speed++;
}