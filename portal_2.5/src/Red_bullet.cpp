//
// Created by Leander on 12/12/2018.
//

#include "Red_bullet.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_bios.h>


int Red_bullet::getx() {
    return static_cast<int>(newX);
}

int Red_bullet::gety() {
    return static_cast<int>(newY);
}

void Red_bullet::setDestination(VECTOR vec) {
    this->dest = vec;
}


void Red_bullet::start(){
    speed = 100;
    time = 0.0166;
    distance = sqrt(pow(fabs(dest.x-static_cast<double>(sprite->getX())),2)+pow(fabs(dest.y-static_cast<double>(sprite->getY())),2));
    directionX = (dest.x-static_cast<double>(sprite->getX())) / distance;
    directionY = (dest.y-static_cast<double>(sprite->getY())) / distance;
    newX = sprite->getX();
    newY = sprite->getY();
    //TextStream::instance().setText(std::to_string(l), 1, 1);
}

// TODO https://gamedev.stackexchange.com/questions/23447/moving-from-ax-y-to-bx1-y1-with-constant-speed
void Red_bullet::tick() {
    newX += (directionX * speed * time);
    newY += (directionY * speed * time);
    teller +=1;
}