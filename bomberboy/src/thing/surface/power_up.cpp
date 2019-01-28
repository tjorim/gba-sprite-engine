//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "power_up.h"
#include "../../../sprites/item_random.h"

PowerUp::PowerUp(int xCoGrid, int yCoGrid) : Surface(xCoGrid, yCoGrid) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(item_randomTiles, sizeof(item_randomTiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCoGrid, 8*yCoGrid)
            .buildPtr());
}

Thing::thingType PowerUp::getType() {
    return thingType::POWERUP;
}
