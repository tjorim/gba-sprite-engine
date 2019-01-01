//
// Created by aydoganmusa on 30.12.18.
//
#include <libgba-sprite-engine/gba_engine.h>
#include "Yamcha.h"

void Yamcha::gotHurt() {
    hurt = true;
    levenspunten = levenspunten - 1;
}

void Yamcha::notGotHurt() {
    hurt = false;
}

void Yamcha::resetYamcha() {
    getSpriteYamcha()->moveTo(GBA_SCREEN_WIDTH - 32, GBA_SCREEN_HEIGHT / 2 + 32);
    getSpriteEnergybarYamcha()->moveTo(GBA_SCREEN_WIDTH - 36, 20);
    getSpriteLifebarYamcha()->moveTo(GBA_SCREEN_WIDTH - 36, 12);
    levenspunten = 300;
    setDood(false);
    getSpriteLifebarYamcha()->animateToFrame(0);
    getSpriteYamcha()->animateToFrame(1);
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

    if ((energypunten < 300) & (energypunten > 200)) {
        getSpriteEnergybarYamcha()->animateToFrame(0);
    } else if ((energypunten < 200) & (energypunten > 100)) {
        getSpriteEnergybarYamcha()->animateToFrame(1);
    } else if ((energypunten < 100) & (energypunten > 0)) {
        getSpriteEnergybarYamcha()->animateToFrame(2);
    } else if ((energypunten == 0)) {
        getSpriteEnergybarYamcha()->animateToFrame(3);
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