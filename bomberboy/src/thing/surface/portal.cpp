//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "portal.h"
#include "../../../sprites/portaal_1.h"

Portal::Portal(int xCoGrid, int yCoGrid) : Surface(xCoGrid, yCoGrid) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(portaal_1Tiles, sizeof(portaal_1Tiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCoGrid, 8*yCoGrid)
            .buildPtr());
}

Thing::thingType Portal::getType() {
    return thingType::PORTAL;
}
