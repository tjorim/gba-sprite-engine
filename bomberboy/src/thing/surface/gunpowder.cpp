//
// Created by tiele on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "gunpowder.h"
#include "../../../sprites/kruit.h"

Gunpowder::Gunpowder(int xCo, int yCo) : Surface(xCo, yCo) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_8_8)
            .withLocation(8*xCo, 8*yCo)
            .buildPtr());
}

Thing::thingType Gunpowder::getType() {
    return thingType::GUNPOWDER;
}
