//
// Created by Tom Fierens on 26/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
#include <libgba-sprite-engine/scene.h>

class death_scene : public Scene {
private:

    int death_score;

public:

    death_scene(const std::shared_ptr<GBAEngine> &engine, int death_score) : Scene(engine), death_score(death_score){}

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};
#endif //GBA_SPRITE_ENGINE_PROJECT_DEATH_SCENE_H
