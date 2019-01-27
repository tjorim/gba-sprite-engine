//
// Created by mathi on 27/01/2019.
//

#include "bowser.h"
std::unique_ptr<AffineSprite>& bowser::getBowserSprite() {
    return bowserSprite;
}

void bowser::kill() {
    dead = true;
}

bool bowser::isDead() {
    return dead;
}

void bowser::tick(u16 keys) {

}
