//
// Created by Dominique on 26/01/2019.
//
#define defaultAmtLives 10

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOSS_H
#define GBA_SPRITE_ENGINE_PROJECT_BOSS_H

#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Boss {
private:
    std::unique_ptr<AffineSprite> bossSprite;
    int amtLives;


public:
    void setAmtLives(int amtLives);
    int getAmtLives() const { return  amtLives; }

    AffineSprite* getBossSprite() const { return bossSprite.get(); }

    Boss(std::unique_ptr<AffineSprite> s) : bossSprite(std::move(s)), amtLives(defaultAmtLives) {};
    //Boss(){};

};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOSS_H