//
// Created by Leander on 18/12/2018.
//

#include "Chell.h"

int Chell::getXSnelheid() const {
    return chell->getDx();
}

int Chell::getYSnelheid() const {
    return chell->getDy();
}

u32 Chell::getXCoordinaat() const {
    return chell->getX();
}

u32 Chell::getYCoordinaat() const {
    return chell->getY();
}



void Chell::setXCoordinaat(u32 xCoodinaat) {
    chell->moveTo(xCoodinaat, chell->getY());
}

void Chell::setYCoordinaat(u32 yCoordinaat) {
    chell->moveTo(chell->getX(), yCoordinaat);
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
