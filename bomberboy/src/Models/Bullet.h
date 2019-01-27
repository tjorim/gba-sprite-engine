//
// Created by Ruben on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BULLET_H
#define GBA_SPRITE_ENGINE_PROJECT_BULLET_H


#include "base_model.h"
#include "../Lib/RCoord.h"

class Bullet : public BaseModel {
private:
    RCoord _vel;
public:
    Bullet(RCoord vel) { _vel = vel;}
    void updateSprite();
    BaseData* getData() {return new BaseData();}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_BULLET_H
