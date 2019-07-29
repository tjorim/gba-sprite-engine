//
// Created by Brecht on 22/01/2019.
//

#include <math.h>
#include "space_ship.h"

#define PI 3.14159265

void SpaceShip::step() {
    if(up){
        vy += gravity - (motorForce * cos(rotation * PI / 180));
        vx -= motorForce * sin(rotation * PI / 180);
    }
    else{
        vy += gravity;
    }
    if(left){
        rotation += rotationSpeed;
    }
    if(right){
        rotation -= rotationSpeed;
    }

    if(rotation < 0){
        rotation = 360 + rotation;
    }

    x += vx;
    y += vy;

    if(x < 0){
        x = 0;
    }
    if(x > 240){
        x = 240;
    }

    if(y < 0){
        y = 0;
    }
    if(y > 160){
        y = 160;
    }
}

float SpaceShip::getX() {
    return x;
}

float SpaceShip::getY() {
    return y;
}

float SpaceShip::getRotation() {
    return rotation;
}

bool SpaceShip::canLand() {
    return (rotation <= 10 || rotation >= 350) && vy < 1 && vx < 0.1;
}

void SpaceShip::restart(){
    x = startX;
    y = startY;
    vx = 0;
    vy = 0;
    rotation = 0;
}