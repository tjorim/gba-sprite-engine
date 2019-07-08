//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SURFACE_H
#define GBA_SPRITE_ENGINE_PROJECT_SURFACE_H

#include "../thing.h"

class Surface : public Thing {
public:
    Surface(int xCoGrid, int yCoGrid, thingType type) : Thing(xCoGrid, yCoGrid, type) {}
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SURFACE_H
