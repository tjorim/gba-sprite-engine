//
// Created by Ruben on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYERDATA_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYERDATA_H

#include "BaseData.h"
#include "../../../demos/demo3-foodthrowing/src/bullet.h"

class PlayerData : public BaseData {
private:
    Bullet* _bullets;
public:
    void setBullents(Bullet* bullets) {_bullets = bullets;}
    Bullet** getBullets() {return &_bullets;}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYERDATA_H
