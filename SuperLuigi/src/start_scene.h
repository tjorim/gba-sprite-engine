//
// Created by mathi on 2/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
class start_scene: public Scene {
private:
    std::unique_ptr<AffineSprite> luigi;
    std::unique_ptr<AffineSprite> goomba;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    start_scene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
