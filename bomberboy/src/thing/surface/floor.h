//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FLOOR_H
#define GBA_SPRITE_ENGINE_PROJECT_FLOOR_H

#include "../surface.h"

class Floor : public Surface {
public:
    Floor(int xCo, int yCo);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_FLOOR_H
