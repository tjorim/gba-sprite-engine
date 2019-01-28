//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SOLID_H
#define GBA_SPRITE_ENGINE_PROJECT_SOLID_H

#include "../thing.h"

class Solid : public Thing {
public:
    Solid(int xCoGrid, int yCoGrid) : Thing(xCoGrid, yCoGrid) {}
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SOLID_H
