//
// Created by Ruben Ponsaers on 3/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_JETJOY_DEAD_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_JETJOY_DEAD_SCENE_H

#include <libgba-sprite-engine/scene.h>

class JetjoyDeadScene : public Scene{
private:
    int score;

public:
    JetjoyDeadScene(const std::shared_ptr<GBAEngine> &engine, int score);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_JETJOY_DEAD_SCENE_H
