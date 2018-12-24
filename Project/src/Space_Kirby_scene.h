//
// Created by Tom Fierens on 7/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ROLLINGSTONE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_ROLLINGSTONE_SCENE_H
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Space_Kirby_scene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sprite> Kirby;
    std::unique_ptr<Sprite> platforms[4];


    bool jumping;
    float dy;

    int middenHoogte, score;


public:
    Space_Kirby_scene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_ROLLINGSTONE_SCENE_H
