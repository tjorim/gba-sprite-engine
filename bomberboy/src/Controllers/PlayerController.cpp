//
// Created by Ruben on 27/01/2019.
//

#include "PlayerController.h"

void PlayerController::processKeys(u16 keys) {
    TextStream::instance().setText("MOVING", 5, 1);
    if(keys & KEY_UP) moveUp();
    if(keys & KEY_DOWN) moveDown();
    if(keys & KEY_LEFT) moveLeft();
    if(keys & KEY_RIGHT) moveRight();
    getModel()->updateSprite();
}

void PlayerController::moveDown() {
    TextStream::instance().setText("MOVE DOWN", 5, 1);
    Dude* dude = dynamic_cast<Dude*>(getModel());
    if(dude != nullptr) {
        dude->move(0, 1);
    }
}

void PlayerController::moveLeft() {
    TextStream::instance().setText("MOVE LEFT", 5, 1);
    Dude* dude = dynamic_cast<Dude*>(getModel());
    if(dude != nullptr) {
        dude->move(-1, 0);
    }
}

void PlayerController::moveRight() {
    TextStream::instance().setText("MOVE RIGHT", 5, 1);
    Dude* dude = dynamic_cast<Dude*>(getModel());
    if(dude != nullptr) {
        dude->move(1, 0);
    }
}

void PlayerController::moveUp() {
    TextStream::instance().setText("MOVE UP", 5, 1);
    Dude* dude = dynamic_cast<Dude*>(getModel());
    if(dude != nullptr) {
        dude->move(0,-1);
    }
}