//
// Created by Leander on 22/12/2018.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "Portal.h"

bool Portal::getOrientation(){
    return orientation;
}

void Portal::setPortal(bool orient, int Xcoor, int Ycoor){
    orientation = orient;
    xCoordinaat = Xcoor;
    yCoordinaat = Ycoor;
    if (orient == true){
        verticalPortal->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT);
        horizontalPortal->moveTo(Xcoor, Ycoor);
    }
    else{
        verticalPortal->moveTo(Xcoor, Ycoor);
        horizontalPortal->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT);
    }
}

int Portal::getXCoordinaat() const {
    return xCoordinaat;
}

int Portal::getYCoordinaat() const {
    return yCoordinaat;
}

bool Portal::getDirection(){
    return direction;
}

void Portal::setDirection(bool dir){
    direction = dir;
}
