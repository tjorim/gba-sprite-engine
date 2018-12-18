//
// Created by joost on 12/12/2018.
//

#include "player.h"

void Player::setRunningsState(bool runningState) {
    this->runningState = runningState;
}

void Player::setDirection(Direction direction) {
    this->direction = direction;
}

void Player::setAantalLevens(int aantalLevens) {
    this->aantalLevens = aantalLevens;
}

/*
Player::Player(int aantalLevens) {
    this->aantalLevens = aantalLevens;
}
*/

Player::Player(const void *imgData, int imgSize, int xC, int yC, SpriteSize spriteSize)  : AffineSprite(imgData, imgSize, xC, yC, spriteSize), aantalLevens(3) {

}
