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
    bool dead;
    int speed;

public:
    Ghost(std::unique_ptr<AffineSprite> s): ghostSprite(std::move(s)), dead(false), speed(1){}
    std::unique_ptr<AffineSprite>& getGhostSprite();
    void explode();
    void revive();
    void incrementSpeed();
    bool isDead(){ return  dead;}
    void tick(u16 keys);

};

#endif //GBA_SPRITE_ENGINE_PROJECT_GHOST_H
