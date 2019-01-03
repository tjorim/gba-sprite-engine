//
// Created by Ruben Ponsaers on 3/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GHOST_H
#define GBA_SPRITE_ENGINE_PROJECT_GHOST_H

#include <libgba-sprite-engine/gba_engine.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Ghost{
private:
    std::unique_ptr<AffineSprite> ghostSprite;

public:
    Ghost(std::unique_ptr<AffineSprite> s): ghostSprite(std::move(s)){}
    Ghost(){}
    std::unique_ptr<AffineSprite>& getGhostSprite();
    void tick(u16 keys);

};

#endif //GBA_SPRITE_ENGINE_PROJECT_GHOST_H
