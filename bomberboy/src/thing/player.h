//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include "../thing.h"

class Player : public Thing {
public:
    Player(int xCoGrid, int yCoGrid);
    void move(int xValue, int yValue);

    thingType getType() override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
