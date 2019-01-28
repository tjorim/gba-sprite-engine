//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GUNPOWDER_H
#define GBA_SPRITE_ENGINE_PROJECT_GUNPOWDER_H

#include "../surface.h"

class Gunpowder : public Surface {
public:
    Gunpowder(int xCo, int yCo);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GUNPOWDER_H
