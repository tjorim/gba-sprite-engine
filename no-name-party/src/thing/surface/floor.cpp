//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "floor.h"
#include "../../../sprites/portaal_2.h"

Floor::Floor(int xCoGrid, int yCoGrid) : Surface(xCoGrid, yCoGrid, thingType::FLOOR) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(portaal_2Tiles, sizeof(portaal_2Tiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCoGrid, 8*yCoGrid)
            .buildPtr());
}
