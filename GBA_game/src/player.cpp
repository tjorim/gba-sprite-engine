//
// Created by joost on 12/12/2018.
//
#define defaultAmtLives 3

#include "player.h"

void Player::setRunningsState(bool runningState) {
    this->runningState = runningState;
}

void Player::setDirection(Direction direction) {
    this->direction = direction;
}

void Player::setAmtLives(int amtLives) {
    this->amtLives = amtLives;
}

void Player::setIsBall(bool isBall){
    this->isBall = isBall;
}

void Player::setCanTakeDamage(bool canTakeDamage){
    this->canTakeDamage = canTakeDamage;
}

void Player::setBallSpeed(int ballSpeed){
    this->ballSpeed = ballSpeed;
}

/*
Player::Player(int amtLives) {
    this->amtLives = amtLives;
}
*/

Player::Player(const void *imgData, int imgSize, int xC, int yC, SpriteSize spriteSize)  : AffineSprite(imgData, imgSize, xC, yC, spriteSize), amtLives(defaultAmtLives) {}
