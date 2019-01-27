//
// Created by Ruben on 27/01/2019.
//

#include "Dude.h"

Dude::Dude() {
    _pos = RCoord(0, 0);
}

Dude::Dude(RCoord pos) {
    _pos = pos;
}

Dude::Dude(int x, int y) {
    _pos = RCoord(x, y);
}

void Dude::updateSprite() {
    TextStream::instance().setText(std::string("Updating sprite to:") + std::to_string(_pos.GetX()) + std::string(" ") + std::to_string(_pos.GetY()), 6, 1);
    getView()->moveTo(_pos.GetX(), _pos.GetY());
}

void Dude::moveTo(RCoord pos) {
    _pos = pos;
}

void Dude::moveTo(int x, int y) {
    _pos.SetX(x);
    _pos.SetY(y);
}

void Dude::move(RCoord pos) {
    _pos += pos;
}

void Dude::move(int x, int y) {
    _pos += RCoord(x, y);
}
