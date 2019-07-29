//
// Created by Leander on 21/12/2018.
//

#include "WallTile.h"

u32 WallTile::getXCoordinaat() const {
    return tile->getX();
}

u32 WallTile::getYCoordinaat() const {
    return tile->getY();
}

bool WallTile::getHasPortal() {
    return hasPortal;
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
