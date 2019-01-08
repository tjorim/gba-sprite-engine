//
// Created by mathi on 7/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_KOOPA_H
#define GBA_SPRITE_ENGINE_PROJECT_KOOPA_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Koopa {
private:
    std::unique_ptr<AffineSprite> koopaSprite;
    bool dead;
    int randomTimer;

public:
    Koopa(std::unique_ptr<AffineSprite> s): koopaSprite(std::move(s)), dead(true), randomTimer(0) {}
    Koopa() {}
    std::unique_ptr<AffineSprite>& getKoopaSprite();
    bool isDead();
    void kill();
    void resurrect();
    void tick(u16 keys);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_KOOPA_H
