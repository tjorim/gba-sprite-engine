//
// Created by Florian on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CHALICE_H
#define GBA_SPRITE_ENGINE_PROJECT_CHALICE_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Chalice {
    private:
        std::unique_ptr<Sprite> chalice;

    public:
        Chalice(std::unique_ptr<Sprite> s1): chalice(std::move(s1)){}


        Sprite *getChaliceSprite() {return chalice.get();}

        void tick(u16 keys);


    };




#endif //GBA_SPRITE_ENGINE_PROJECT_CHALICE_H
