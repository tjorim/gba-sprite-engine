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
    if ((levenspunten < 300) & (levenspunten > 200)) {
        getSpriteLifebarYamcha()->animateToFrame(0);
    } else if ((levenspunten < 200) & (levenspunten > 100)) {
        getSpriteLifebarYamcha()->animateToFrame(1);
    } else if ((levenspunten < 100) & (levenspunten > 0)) {
        getSpriteLifebarYamcha()->animateToFrame(2);
    } else if ((levenspunten == 0)) {
        getSpriteLifebarYamcha()->animateToFrame(3);
        setDood(true);
    }

    if (hurt) {
        getSpriteYamcha()->animateToFrame(0);
    } else {
        getSpriteYamcha()->animateToFrame(1);
    }
}

void Yamcha::setDood(bool input) {
    dood = input;
}

bool Yamcha::isdood() {
    return dood;
}