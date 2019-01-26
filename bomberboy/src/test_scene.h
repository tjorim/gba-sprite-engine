//
// Created by JT
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H


#include <libgba-sprite-engine/scene.h>

class TestScene : public Scene {
private:
    int counter = 0;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    TestScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
