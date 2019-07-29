//
// Created by Florian on 26/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SKELETON_H
#define GBA_SPRITE_ENGINE_PROJECT_SKELETON_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Ghost{
private:
    std::unique_ptr<Sprite> ghost;
    bool attack = false;

public:
    Ghost(std::unique_ptr<Sprite> s): ghost(std::move(s)){}

    Sprite *getGhostSprite() {return ghost.get();}

    void setAttack(bool value);
    void tick(u16 keys);


};



#endif //GBA_SPRITE_ENGINE_PROJECT_SKELETON_H
