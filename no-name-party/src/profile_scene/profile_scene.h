//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H

#include <libgba-sprite-engine/scene.h>

class ProfileScene : public Scene {
private:
    std::unique_ptr<Background> background_profile;

    bool a_last = false, b_last = false;
    bool a_now = false, b_now = false;

public:
    ProfileScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H
