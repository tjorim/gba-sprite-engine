//
// Created by Jolien Jeunen on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H

#include <libgba-sprite-engine/scene.h>

class StartScene : public Scene {
private:
    std::unique_ptr<Sprite> flappyBird;
    std::unique_ptr<Background> startbg;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    StartScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};

#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
