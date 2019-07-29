//
// Created by Florian on 26/01/2019.
//

#include "Ghost.h"
#include <libgba-sprite-engine/gba/tonc_types.h>

void Ghost::setAttack(bool value) {
    attack = value;
}
void Ghost::tick(u16 keys) {
    getGhostSprite()->setVelocity(-1,0);
    /*if(attack == true){
        getGhostSprite()->setVelocity(0,0);
        getGhostSprite()->makeAnimated(4,20);
        setAttack(false);
        getGhostSprite()->animateToFrame(1);
    }*/

}