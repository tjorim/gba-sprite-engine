//
// Created by laura on 1/28/2019.
//

#include "Enemy.h"

void Enemy::update() {
    ++counter;
    if (posX > 160) {
        if(counter >= 4) {
            --posX;
            counter = 0;
        }

    }

    else if(posX == 160){
        posX = 170;
        if(counter >= 4) {
            --posX;
            counter = 0;
        }
    }

    eendje->flipHorizontally(true);
    eendje->moveTo(posX, posY);
    //TextStream::instance().setText(std::to_string(posX), 1,1);
}
void Enemy::kill(){
    posX = 260;
}