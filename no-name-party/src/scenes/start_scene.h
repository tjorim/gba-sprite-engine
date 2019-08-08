//
// Created by Jorim Tielemans
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../balloon.h"
#include "../cloud.h"
#include "../press_start.h"
#include "../title.h"

class StartScene : public Scene {
private:
    std::unique_ptr<Background> bg_map;
    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std::vector<std::unique_ptr<Balloon>> balloons;
    std::unique_ptr<Cloud> cloud;
    std::unique_ptr<PressStart> press_start;
    std::unique_ptr<Title> title;

public:
    StartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H