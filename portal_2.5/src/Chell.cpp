//
// Created by Leander on 18/12/2018.
//

#include "Chell.h"

u32 Chell::getXCoordinaat() const {
    return chell->getX();
}

u32 Chell::getYCoordinaat() const {
    return chell->getY();
}

void Chell::setXSnelheid(int xSnelheid) {
    chell->setVelocity(xSnelheid, chell->getDy());
}

void Chell::setYSnelheid(int ySnelheid) {
    chell->setVelocity(chell->getDx(), ySnelheid);
}

void Chell::setLocation(int x, int y){
    chell->moveTo(x, y);
}


void Chell::doJump(){
    if ((chell->getDy() == 0) && jump == false) {
        jump = true;
        chellRefY = chell->getY();
    }
}

int Chell::controleJump(){
    if( chell->getY() <= chellRefY-springhoogte){
        jump = false;
    }
    if(jump == true){
        return -2;
    }
    return 1;
}

