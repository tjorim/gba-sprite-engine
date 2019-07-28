//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
#define GBA_SPRITE_ENGINE_PROJECT_BALLOON_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Balloon {
private:
    std::unique_ptr<Sprite> sprite;

public:
    Balloon(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {} // int xCo, int yCo

    Sprite* getSprite() { return sprite.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
