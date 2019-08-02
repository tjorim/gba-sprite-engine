//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECT_H
#define GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECT_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Character_select {
private:
    std::unique_ptr<Sprite> sprite;

    bool selected = false;

public:
    Character_select(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {}

    Sprite* getSprite() { return sprite.get(); }

    void select() { selected = true; }
    void unselect() { selected = false; }
}

#endif // GBA_SPRITE_ENGINE_PROJECT_CHARACTER_SELECT_H