//
// Created by Leander on 21/12/2018.
//

#include "WallTile.h"

u32 WallTile::getXSnelheid() const {
    return tile->getDx();
}

u32 WallTile::getYSnelheid() const {
    return tile->getDy();
}

u32 WallTile::getXCoordinaat() const {
    return tile->getX();
}

u32 WallTile::getYCoordinaat() const {
    return tile->getY();
}

bool WallTile::getHasPortal() {
    return hasPortal;
}


void WallTile::setXCoodinaat(u32 xCoodinaat) {
    tile->moveTo(xCoodinaat, tile->getY());
}

void WallTile::setYCoordinaat(u32 yCoordinaat) {
    tile->moveTo(tile->getX(), yCoordinaat);
}

void WallTile::setXSnelheid(u32 xSnelheid) {
    tile->setVelocity(xSnelheid, tile->getDy());
}

void WallTile::setYSnelheid(u32 ySnelheid) {
    tile->setVelocity(tile->getDy(), ySnelheid);
}

void WallTile::setHasPortal(bool portal) {
    hasPortal = portal;
}

void WallTile::updateView(){
    if (hasPortal == true){
        tile->animateToFrame(1);
    }
    else{
        tile->animateToFrame(0);
    }
}
