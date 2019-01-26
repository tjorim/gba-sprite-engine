//
// Created by joost on 29/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H

#include "../../engine/include/libgba-sprite-engine/background/background.h"
#include "../../engine/include/libgba-sprite-engine/sprites/sprite.h"
#include "../../engine/include/libgba-sprite-engine/gba_engine.h"
#include "../../engine/include/libgba-sprite-engine/gba/tonc_types.h"

class StartScene : public Scene {
private:
    std::unique_ptr<Background> bg;
    int scrollX, scrollY;
    int rotation;
    int rotationDiff = 128;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    StartScene(std::shared_ptr<GBAEngine> engine) : Scene(engine), rotation(0), rotationDiff(128), scrollX(0), scrollY(0) {}

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H
