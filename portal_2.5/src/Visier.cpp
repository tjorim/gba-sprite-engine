//
// Created by Leander on 22/12/2018.
//

#include "Visier.h"

int Visier::getXSnelheid() const {
    return visier->getDx();
}

int Visier::getYSnelheid() const {
    return visier->getDy();
}

u32 Visier::getXCoordinaat() const {
    return visier->getX();
}

u32 Visier::getYCoordinaat() const {
    return visier->getY();
}

int Visier::getPc(){
    return visier->getMatrix()->pc;
}

bool Visier::getFlipVisier(){
    return flipVisier;
}

void Visier::setXCoodinaat(u32 xCoodinaat) {
    visier->moveTo(xCoodinaat, visier->getY());
}

void Visier::setYCoordinaat(u32 yCoordinaat) {
    visier->moveTo(visier->getX(), yCoordinaat);
}

void Visier::setXSnelheid(int xSnelheid) {
    visier->setVelocity(xSnelheid, visier->getDy());
}

void Visier::setYSnelheid(int ySnelheid) {
    visier->setVelocity(visier->getDx(), ySnelheid);
}

void Visier::setLocation(int x, int y){
    visier->moveTo(x, y);
}

void Visier::rotate(bool richting) {
    if (richting == true){
        visierRotation -= 300;
    }
    else{
        visierRotation += 300;
    }
    visier->rotate(visierRotation);
    if (visier->getMatrix()->pa < 0) {
        flipVisier = true;
    } else { flipVisier = false; }
}