//
// Created by Ruben Ponsaers on 30/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_JETJOY_START_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_JETJOY_START_SCENE_H

#include <libgba-sprite-engine/scene.h>

class JetjoyStartScene : public Scene{
private:
    // nothing yet
public:
    JetjoyStartScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_JETJOY_START_SCENE_H
