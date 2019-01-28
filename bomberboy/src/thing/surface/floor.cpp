//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "floor.h"
#include "../../../sprites/portaal_2.h"

Floor::Floor(int xCo, int yCo) : Surface(xCo, yCo) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(portaal_2Tiles, sizeof(portaal_2Tiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCo, 8*yCo)
            .buildPtr());
}

Thing::thingType Floor::getType() {
    return thingType::FLOOR;
}
