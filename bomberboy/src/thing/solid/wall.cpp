//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "wall.h"
#include "../../../sprites/muur.h"

Wall::Wall(int xCo, int yCo) : Solid(xCo, yCo) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(muurTiles, sizeof(muurTiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCo, 8*yCo)
            .buildPtr());
}

Thing::thingType Wall::getType() {
    return thingType::WALL;
}
