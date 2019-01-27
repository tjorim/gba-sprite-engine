//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_THING_H
#define GBA_SPRITE_ENGINE_PROJECT_THING_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Thing {
private:
    std::unique_ptr<Sprite> sprite;
public:
    Thing(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}

    Sprite* getSprite() { return sprite.get(); }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_THING_H
