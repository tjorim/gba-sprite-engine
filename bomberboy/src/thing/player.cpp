//
// Created by tiele on 27/01/2019.
//

#include "player.h"

    playerSprite = spriteBuilder
            ->withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_8_16)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

void Player::move(int xValue, int yValue) {
    setXCo(xValue);
    setYCo(yValue);
    sprite->moveTo(8*xValue, 8*(yValue-1));
}