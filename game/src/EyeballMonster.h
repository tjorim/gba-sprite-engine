//
// Created by Florian on 6/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_EYEBALLMONSTER_H
#define GBA_SPRITE_ENGINE_PROJECT_EYEBALLMONSTER_H

#include <libgba-sprite-engine/sprites/sprite.h>

class EyeballMonster {
private:
    std::unique_ptr<Sprite> eyeball;

public:
    EyeballMonster(std::unique_ptr<Sprite> s): eyeball(std::move(s)){}

    Sprite *getEyeballSprite() {return eyeball.get();}
    void tick(u16 keys);


};
#endif //GBA_SPRITE_ENGINE_PROJECT_EYEBALLMONSTER_H
