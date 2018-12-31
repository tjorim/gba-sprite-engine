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
    getSpriteGoku()->flipHorizontally(omkeren);

    if (levenspunten == 300) {
        getSpriteLifebarGoku()->animateToFrame(0);
    } else if ((levenspunten < 300) & (levenspunten > 150)) {
        getSpriteLifebarGoku()->animateToFrame(1);
    } else if ((levenspunten < 151) & (levenspunten > 75)) {
        getSpriteLifebarGoku()->animateToFrame(2);
    }

    if (moveRight) {
        getSpriteGoku()->setVelocity(+2, 0);
        getSpriteGoku()->animateToFrame(4);
        omkeren = false;
    } else if (moveLeft) {
        getSpriteGoku()->setVelocity(-2, 0);
        getSpriteGoku()->animateToFrame(4);
        omkeren = true;
    } else if (kick) {
        getSpriteGoku()->animateToFrame(3);
    } else if (hit) {
        getSpriteGoku()->animateToFrame(2);
    } else {
        getSpriteGoku()->setVelocity(0, 0);
        getSpriteGoku()->animateToFrame(0);
    }
}