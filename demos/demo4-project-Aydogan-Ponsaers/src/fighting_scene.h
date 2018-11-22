//
// Created by aydoganmusa on 22.11.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>

class FightingScene : public Scene {
private:
    std::unique_ptr<Sprite> goku;

public:
    explicit FightingScene(const std::shared_ptr<GBAEngine>) : Scene(engine) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 i) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
