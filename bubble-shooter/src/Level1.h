//
// Created by 11401165 on 21/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H

#include "SceneLevel1.h"



class Level1: public SceneLevel1 {
private:
    void tick(u16 keys) override;
    void load()override;
    void atStartGame() override;

public:

    Level1(std::shared_ptr<GBAEngine> engine,int start_score): SceneLevel1(engine,start_score){}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
