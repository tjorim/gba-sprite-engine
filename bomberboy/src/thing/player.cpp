//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "../../sprites/blauw_dood.h"

Player::Player(int xCoGrid, int yCoGrid) : Thing(xCoGrid, yCoGrid) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(blauw_doodTiles, sizeof(blauw_doodTiles))
            .withSize(SIZE_8_16)
            .withLocation(8*xCoGrid, 8*(yCoGrid-1))
            .buildPtr());
}

void Player::move(int xValue, int yValue) {
    setXCoGrid(xValue);
    setYCoGrid(yValue);
    getSprite()->moveTo(8*xValue, 8*(yValue-1));
}

Thing::thingType Player::getType() {
    return thingType::PLAYER;
}
