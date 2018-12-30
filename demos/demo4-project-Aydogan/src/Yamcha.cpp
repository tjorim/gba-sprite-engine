//
// Created by aydoganmusa on 30.12.18.
//
#include "Yamcha.h"

void Yamcha::gotHurt() {
    hurt = true;
}

void Yamcha::notGotHurt() {
    hurt = false;
}

void Yamcha::tick() {
    if (hurt) {
        getSprite()->animateToFrame(0);
    } else {
        getSprite()->animateToFrame(1);
    }
}