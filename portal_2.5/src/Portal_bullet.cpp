//
// Created by Leander on 12/12/2018.
//

#include "Portal_bullet.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_bios.h>


int Portal_bullet::getx() {
    return static_cast<int>(newX);
}

int Portal_bullet::gety() {
    return static_cast<int>(newY);
}

void Portal_bullet::setDestination(int pc, int X, int Y, int With) {

    double sinus = static_cast<double>(pc)/(With*4);
    double angle = (asin(sinus)*180.0)/ 3.1415;
    double tanges = tan((angle* 3.1415 )/ 180.0);
    double y = tanges*20;
    dest.x = (X + 28) + 20;
    dest.y = (Y + 28) - static_cast<int>(y);

    //TextStream::instance().setText(std::to_string(X), 1, 1);


}


void Portal_bullet::start(bool flip){
    speed = 100;
    time = 0.0166;
    distance = sqrt(pow(fabs(dest.x-static_cast<double>(sprite->getX())),2)+pow(fabs(dest.y-static_cast<double>(sprite->getY())),2));
    directionX = (dest.x-static_cast<double>(sprite->getX())) / distance;
    directionY = (dest.y-static_cast<double>(sprite->getY())) / distance;
    newX = sprite->getX();
    newY = sprite->getY();
    flip_visier = flip;

}

// TODO https://gamedev.stackexchange.com/questions/23447/moving-from-ax-y-to-bx1-y1-with-constant-speed
void Portal_bullet::tick() {
    if (flip_visier == true){
        newX -= (directionX * speed * time);
    }
    else {      newX += (directionX * speed * time);

    }
    newY += (directionY * speed * time);
    teller +=1;
    //TextStream::instance().setText(std::to_string(distance), 1, 1);
}