//
// Created by Jorim Tielemans
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class SelectScene : public Scene {
private:
    int level = 1;

    void levelUp();
    void levelDown();

public:
    SelectScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;

    int getLevel() const;
    void setLevel(int level);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H