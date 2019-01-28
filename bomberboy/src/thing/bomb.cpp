//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "bomb.h"
#include "../../sprites/bom.h"

Bomb::Bomb(int xCoGrid, int yCoGrid) : Thing(xCoGrid, yCoGrid) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(bomTiles, sizeof(bomTiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCoGrid, 8*yCoGrid)
            .buildPtr());
}

Thing::thingType Bomb::getType() {
    return thingType::BOMB;
}
