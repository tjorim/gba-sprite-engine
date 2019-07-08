//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "crate.h"
#include "../../../sprites/krat.h"

Crate::Crate(int xCoGrid, int yCoGrid) : Solid(xCoGrid, yCoGrid, thingType::CRATE) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(kratTiles, sizeof(kratTiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCoGrid, 8*yCoGrid)
            .buildPtr());
}
    