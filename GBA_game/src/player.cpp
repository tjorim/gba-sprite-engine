//
// Created by joost on 12/12/2018.
//

#include "player.h"



void Player::setDirection(Direction direction) {
    this->direction = direction;
}

void Player::setAantalLevens(int aantalLevens) {
    this->aantalLevens = aantalLevens;
}

Player::Player(int aantalLevens) {
    this->aantalLevens = aantalLevens;
}