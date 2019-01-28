//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PORTAL_H
#define GBA_SPRITE_ENGINE_PROJECT_PORTAL_H

#include "../surface.h"

class Portal : public Surface {
public:
    Portal(int xCoGrid, int yCoGrid);

    thingType getType() override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PORTAL_H
