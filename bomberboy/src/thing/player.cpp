//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "../../sprites/blauw_dood.h"

Player::Player(int xCo, int yCo) : Thing(xCo, yCo) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(blauw_doodTiles, sizeof(blauw_doodTiles))
            .withSize(SIZE_8_16)
            .withLocation(8*xCo, 8*(yCo-1))
            .buildPtr());
}

void Player::move(int xValue, int yValue) {
    setXCo(xValue);
    setYCo(yValue);
    getSprite()->moveTo(8*xValue, 8*(yValue-1));
}

Thing::thingType Player::getType() {
    return thingType::PLAYER;
}
