//
// Created by laura on 1/28/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMY_H


#include <bits/unique_ptr.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>

class Enemy {

private:
    std::unique_ptr<Sprite> eendje;
    int posX = 260;
    int posY = 135;
    int counter = 0;
public:
    Enemy(std::unique_ptr<Sprite> sprite):eendje(std::move(sprite)){
        eendje->flipHorizontally(true);
    };
    void update();
    Sprite* getSprite(){
        eendje.get();
    }
    int getX(){
        return posX;
    }
    int getY() {
        return posY;
    }
    void setY(int y){
       posY = y;
    }
    void kill();

};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
