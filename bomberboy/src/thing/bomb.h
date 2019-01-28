//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOMB_H
#define GBA_SPRITE_ENGINE_PROJECT_BOMB_H

#include "../thing.h"

class Bomb : public Thing {
public:
    Bomb(int xCoGrid, int yCoGrid);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOMB_H
