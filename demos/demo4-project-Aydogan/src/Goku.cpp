//
// Created by aydoganmusa on 29.12.18.
//
#include <libgba-sprite-engine/gba_engine.h>
#include "Goku.h"

void Goku::setChargeSpecialAttack(bool input) {
    charge = input;
}

bool Goku::getChargeSpecialAttack() {
    return charge;
}


void Goku::setSpecialAttack(bool input) {
    specialAttack = input;
}

bool Goku::getSpecialAttack() {
    return specialAttack;
}

void Goku::setMoveLeft(bool input) {
    moveLeft = input;
}

bool Goku::getMoveLeft() {
    return moveLeft;
}

void Goku::setMoveRight(bool input) {
    moveRight = input;
}

bool Goku::getMoveRight() {
    return moveRight;
}

void Goku::setKick(bool input) {
    kick = input;
}

bool Goku::getKick() {
    return kick;
}

void Goku::setHit(bool input) {
    hit = input;
}

bool Goku::getHit() {
    return hit;
}

void Goku::setDood(bool input) {
    dood = input;
}

bool Goku::getDood() {
    return dood;
}

void Goku::resetGoku() {
    getSpriteGoku()->moveTo(16, GBA_SCREEN_HEIGHT / 2 + 32);
    getSpriteEnergybarGoku()->moveTo(4, 20);
    getSpriteLifebarGoku()->moveTo(4, 12);
    getSpriteWaveGoku()->moveTo(-64, -32);
    levenspunten = 300;
    energypunten = 300;
    setSpecialAttack(false);
    setKick(false);
    setHit(false);
    setMoveLeft(false);
    setMoveRight(false);
    setChargeSpecialAttack(false);
    getSpriteLifebarGoku()->animateToFrame(0);
    getSpriteEnergybarGoku()->animateToFrame(0);
    getSpriteGoku()->animateToFrame(0);
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

    if (getMoveRight()) {
        getSpriteGoku()->setVelocity(+2, 0);
        getSpriteGoku()->animateToFrame(3);
        omkeren = false;
    } else if (getMoveLeft()) {
        getSpriteGoku()->setVelocity(-2, 0);
        getSpriteGoku()->animateToFrame(3);
        omkeren = true;
    } else if (getKick()) {
        getSpriteGoku()->animateToFrame(2);
    } else if (getHit()) {
        getSpriteGoku()->animateToFrame(1);
    } else if (getChargeSpecialAttack()) {
        if (energypunten > 0 && charging < 40 && !getSpecialAttack()) {
            getSpriteGoku()->animateToFrame(4);
            charging++;
        } else {
            setChargeSpecialAttack(false);
            setSpecialAttack(energypunten > 0 && charging > 39);
        }
    } else if (getSpecialAttack()) {
        if (energypunten > 0 && charging > 0 && !getChargeSpecialAttack()) {
            getSpriteGoku()->animateToFrame(5);
            getSpriteWaveGoku()->moveTo(getSpriteGoku()->getX() + 30, getSpriteGoku()->getY());
            energypunten = energypunten - 3;
            charging--;
        } else {
            setSpecialAttack(false);
            getSpriteWaveGoku()->moveTo(-64, -32);
        }
    } else {
        getSpriteGoku()->setVelocity(0, 0);
        getSpriteGoku()->animateToFrame(0);
        getSpriteWaveGoku()->moveTo(-64, -32);
    }
}