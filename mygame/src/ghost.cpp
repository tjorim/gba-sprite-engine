//
// Created by Ruben Ponsaers on 3/01/2019.
//

#include "ghost.h"

std::unique_ptr<AffineSprite>& Ghost::getGhostSprite() {
    return ghostSprite;
}

void Ghost::tick(u16 keys) {
    ghostSprite->setVelocity(-3,0);

    if(ghostSprite->isOffScreen()){
        ghostSprite->moveTo(GBA_SCREEN_WIDTH,rand() % 140);
    }

}