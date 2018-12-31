//
// Created by aydoganmusa on 29.12.18.
//
#include <libgba-sprite-engine/gbavector.h>
#include "Goku.h"

void Goku::doChargeSpecialAttack() {
    charge = true;
    if (charging < 40 and energypunten > 0) {
        charging++;
    } else {
        doSpecialAttack();
    }
}

void Goku::doNotChargeSpecialAttack() {
    charge = false;
    charging = 0;
}

void Goku::doSpecialAttack() {
    charge = false;
    if (energypunten > 0) {
        specialAttack = true;
        energypunten = energypunten - 3;
    } else {
        doNotSpecialAttack();
    }
}

void Goku::doNotSpecialAttack() {
    specialAttack = false;
}

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

void Goku::setDood(bool input) {
    dood = input;
}

bool Goku::isdood() {
    return dood;
}

void Goku::tick() {
    getSpriteGoku()->flipHorizontally(omkeren);

    if ((levenspunten < 300) & (levenspunten > 200)) {
        getSpriteLifebarGoku()->animateToFrame(0);
    } else if ((levenspunten < 200) & (levenspunten > 100)) {
        getSpriteLifebarGoku()->animateToFrame(1);
    } else if ((levenspunten < 100) & (levenspunten > 0)) {
        getSpriteLifebarGoku()->animateToFrame(2);
    } else if ((levenspunten == 0)) {
        getSpriteLifebarGoku()->animateToFrame(3);
        setDood(true);
    }

    if ((energypunten < 300) & (energypunten > 200)) {
        getSpriteEnergybarGoku()->animateToFrame(0);
    } else if ((energypunten < 200) & (energypunten > 100)) {
        getSpriteEnergybarGoku()->animateToFrame(1);
    } else if ((energypunten < 100) & (energypunten > 0)) {
        getSpriteEnergybarGoku()->animateToFrame(2);
    } else if ((energypunten == 0)) {
        getSpriteEnergybarGoku()->animateToFrame(3);
    }

    if (moveRight) {
        getSpriteGoku()->setVelocity(+2, 0);
        getSpriteGoku()->animateToFrame(3);
        omkeren = false;
    } else if (moveLeft) {
        getSpriteGoku()->setVelocity(-2, 0);
        getSpriteGoku()->animateToFrame(3);
        omkeren = true;
    } else if (kick) {
        getSpriteGoku()->animateToFrame(2);
    } else if (hit) {
        getSpriteGoku()->animateToFrame(1);
    } else if (charge) {
        getSpriteGoku()->animateToFrame(4);
    } else if (specialAttack) {
        getSpriteGoku()->animateToFrame(5);
        getSpriteWaveGoku()->moveTo(getSpriteGoku()->getX() + 30, getSpriteGoku()->getY());
    } else {
        getSpriteGoku()->setVelocity(0, 0);
        getSpriteGoku()->animateToFrame(0);
        getSpriteWaveGoku()->moveTo(-64, -32);
    }
}