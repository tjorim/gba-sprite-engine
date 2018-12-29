//
// Created by Wout Briels on 26/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL2SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL2SCENE_H


#include <libgba-sprite-engine/scene.h>

class Level2Scene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sprite> player;

    int bgX, bgY;

public:
    Level2Scene(std::shared_ptr<GBAEngine> engine) : Scene(engine), bgX(0), bgY(96) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL2SCENE_H
