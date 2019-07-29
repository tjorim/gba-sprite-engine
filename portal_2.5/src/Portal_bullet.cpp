//
// Created by Leander on 12/12/2018.
//

#include "Portal_bullet.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_bios.h>
#include <libgba-sprite-engine/gba_engine.h>


int Portal_bullet::getx() {
    return bullet->getX();
}

int Portal_bullet::gety() {
    return bullet->getY();
}

void Portal_bullet::setx(int x) {
     bullet->moveTo(x, bullet->getY());
}

void Portal_bullet::sety(int y) {
     bullet->moveTo(bullet->getX(), y);
}

bool Portal_bullet::getIsMoving() {
    return isMoving;
}

void Portal_bullet::setIsMoving(bool move) {
    isMoving = move;
}


void Portal_bullet::setDestination(int pc, int X, int Y, int With) {

    double sinus = static_cast<double>(pc)/(With*4);
    double angle = (asin(sinus)*180.0)/ 3.1415;
    double tanges = tan((angle* 3.1415 )/ 180.0);
    double y = tanges*20;
    dest.x = (X + 28) + 20;
    dest.y = (Y + 28) - static_cast<int>(y);
}


void Portal_bullet::start(bool flip, int xLoc, int yLoc){
    speed = 500;
    time = 0.0166;
    distance = sqrt(pow(fabs(dest.x-static_cast<double>(xLoc)),2)+pow(fabs(dest.y-static_cast<double>(yLoc)),2));
    directionX = (dest.x-static_cast<double>(xLoc)) / distance;
    directionY = (dest.y-static_cast<double>(yLoc)) / distance;
    newX = xLoc;
    newY = yLoc;
    flip_visier = flip;

}

// TODO https://gamedev.stackexchange.com/questions/23447/moving-from-ax-y-to-bx1-y1-with-constant-speed
void Portal_bullet::tick() {
    if(isMoving) {
        if (flip_visier == true) {
            newX -= (directionX * speed * time);
        } else {
            newX += (directionX * speed * time);
        }
        newY += (directionY * speed * time);
        bullet->moveTo(newX, newY);

        if (bullet->isOffScreen()) {
            isMoving = false;
            bullet->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT);
        }
    }
    else{
        bullet->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT);
    }
}