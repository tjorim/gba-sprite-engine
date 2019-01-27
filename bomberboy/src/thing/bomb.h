//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOMB_H
#define GBA_SPRITE_ENGINE_PROJECT_BOMB_H

#include "../thing.h"

class Bomb : public Thing {
public:
    Bomb(std::unique_ptr<Sprite> sprite) : Thing(std::move(sprite)) {}
};


#endif //GBA_SPRITE_ENGINE_PROJECT_BOMB_H
