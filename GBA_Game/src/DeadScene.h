//
// Created by Wout Briels on 3/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DEADSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_DEADSCENE_H


#include <libgba-sprite-engine/scene.h>

class DeadScene : public Scene {
private:

public:
    DeadScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_DEADSCENE_H
