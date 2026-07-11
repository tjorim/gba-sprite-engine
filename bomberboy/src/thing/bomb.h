//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOMB_H
#define GBA_SPRITE_ENGINE_PROJECT_BOMB_H

#include "../thing.h"

class Bomb : public Thing {
private:
    int ticksUntilExplosion = 120;

public:
    Bomb(int xCoGrid, int yCoGrid);

    bool tick();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOMB_H
