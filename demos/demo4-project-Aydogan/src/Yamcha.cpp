//
// Created by aydoganmusa on 30.12.18.
//
#include "Yamcha.h"

void Yamcha::gotHurt() {
    hurt = true;
    levenspunten = levenspunten - 1;
}

void Yamcha::notGotHurt() {
    hurt = false;
}

void Yamcha::tick() {
    if (levenspunten == 300) {
        getSpriteLifebarYamcha()->animateToFrame(0);
    } else if ((levenspunten < 300) & (levenspunten > 150)) {
        getSpriteLifebarYamcha()->animateToFrame(1);
    } else if ((levenspunten < 151) & (levenspunten > 75)) {
        getSpriteLifebarYamcha()->animateToFrame(2);
    }

    if (hurt) {
        getSpriteYamcha()->animateToFrame(0);
    } else {
        getSpriteYamcha()->animateToFrame(1);
    }
}