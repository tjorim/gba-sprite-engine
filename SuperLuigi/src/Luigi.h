//
// Created by Vandebosch Remy on 19/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LUIGI_H
#define GBA_SPRITE_ENGINE_PROJECT_LUIGI_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Luigi {
private:
    std::unique_ptr<AffineSprite> luigiSprite;

public:
    Luigi(std::unique_ptr<AffineSprite> s) : luigiSprite(std::move(s)) {}
    Luigi() {}
    std::unique_ptr<AffineSprite>& getLuigiSprite();
    void tick(u16 keys);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_LUIGI_H
