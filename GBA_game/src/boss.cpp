//
// Created by Dominique on 26/01/2019.
//

#include "boss.h"

#define defaultAmtLives 10

void Boss::setAmtLives(int amtLives) {
    this->amtLives = amtLives;
}

std::unique_ptr<AffineSprite>& Boss::getBossSprite() {
    return bossSprite;
}

Boss::Boss(std::unique_ptr<AffineSprite> s) : bossSprite(getBossSprite()) , amtLives(defaultAmtLives) {}

