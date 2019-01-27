//
// Created by mathi on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOWSER_H
#define GBA_SPRITE_ENGINE_PROJECT_BOWSER_H
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class bowser {
private:
    std::unique_ptr<AffineSprite> bowserSprite;
    bool dead;
    int randomTimer;

public:
    bowser(std::unique_ptr<AffineSprite> s) : bowserSprite(std::move(s)), dead(false), randomTimer(0) {}
    bowser() {}
    std::unique_ptr<AffineSprite>& getBowserSprite();
    void tick(u16 keys) ;
    void kill();
    bool isDead();
    void timer();
    int getTimer();


};


#endif //GBA_SPRITE_ENGINE_PROJECT_BOWSER_H
