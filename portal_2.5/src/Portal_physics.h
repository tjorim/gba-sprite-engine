//
// Created by Leander on 11/12/2018.
//

#include <libgba-sprite-engine/sprites/sprite.h>

class Portal_physics {
private:
    std::unique_ptr<Sprite> sprite;



public:
    Portal_physics(std::unique_ptr<Sprite> sprite) {
    }

    void move();
};