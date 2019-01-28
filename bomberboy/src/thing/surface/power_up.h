//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_POWER_UP_H
#define GBA_SPRITE_ENGINE_PROJECT_POWER_UP_H

#include "../surface.h"

class PowerUp : public Surface {
public:
    PowerUp(int xCo, int yCo);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_POWER_UP_H
