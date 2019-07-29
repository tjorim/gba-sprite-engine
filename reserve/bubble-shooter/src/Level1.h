//
// Created by 11401165 on 21/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H

#include "SceneLevel1.h"



class Level1: public SceneLevel1 {
private:
    //int score;
    //std::vector<std::unique_ptr<Ball>> ballen;
    //std::vector<std::unique_ptr<Sprite>> bullets;
public:

    //Level1(std::shared_ptr<GBAEngine> engine,int start_score): SceneLevel1(engine,start_score){}
    Level1(std::shared_ptr<GBAEngine> engine): SceneLevel1(engine){}
    void tick(u16 keys);
    void load();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
