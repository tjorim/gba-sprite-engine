//
// Created by Leander on 18/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_CHELL_H
#define GBA_SPRITE_ENGINE_PROJECT_CHELL_H


#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/sprites/sprite.h>

class Chell {

private:
    std::unique_ptr<Sprite> chell;
    bool jump = false;
    u32 chellRefY;
    u32 springhoogte = 25;

public:
    Chell(std::unique_ptr<Sprite> sprite) : chell(std::move(sprite)){};

    void doJump();
    int controleJump();
    void Collisiondetection();
    u32 getXCoordinaat() const;
    u32 getYCoordinaat() const;
    void setXSnelheid(int xSnelheid);
    void setYSnelheid(int ySnelheid);
    void setLocation(int x, int y);
    Sprite* getSprite() { return chell.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_CHELL_H
