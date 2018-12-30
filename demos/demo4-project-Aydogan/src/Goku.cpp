//
// Created by aydoganmusa on 29.12.18.
//
#include <libgba-sprite-engine/gbavector.h>
#include "Goku.h"

void Goku::doMoveLeft() {
    moveLeft = true;
}

void Goku::doNotMoveLeft() {
    moveLeft = false;
}

void Goku::doMoveRight() {
    moveRight = true;
}

void Goku::doNotMoveRight() {
    moveRight = false;
}

void Goku::doKick() {
    kick = true;
}

void Goku::doNotKick() {
    kick = false;
}

void Goku::doHit() {
    hit = true;
}

void Goku::doNotHit() {
    hit = false;
}

void Goku::tick() {
    getSprite()->flipHorizontally(omkeren);
    if (moveRight) {
        getSprite()->setVelocity(+1, 0);
        getSprite()->animateToFrame(4);
        omkeren = false;
    } else if (moveLeft) {
        getSprite()->setVelocity(-1, 0);
        getSprite()->animateToFrame(4);
        omkeren = true;
    } else if (kick) {
        getSprite()->animateToFrame(3);
    } else if (hit) {
        getSprite()->animateToFrame(2);
    } else {
        getSprite()->setVelocity(0, 0);
        getSprite()->animateToFrame(0);
    }
}