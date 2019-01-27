//
// Created by tiele on 27/01/2019.
//

#include "crate.h"

    crateSprite = spriteBuilder
            ->withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_8_8)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();