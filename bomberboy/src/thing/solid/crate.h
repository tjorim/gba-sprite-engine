//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CRATE_H
#define GBA_SPRITE_ENGINE_PROJECT_CRATE_H

#include "../solid.h"

class Crate : public Solid {
public:
    Crate(int xCo, int yCo);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_CRATE_H
