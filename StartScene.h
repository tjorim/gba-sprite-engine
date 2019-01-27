//
// Created by lloyd on 29-Nov-18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include "Direction.h"

class StartScene : public Scene {
private:
    //std::unique_ptr<Sprite> walkUpAnimation;
    std::unique_ptr<Sprite> linkAnimation;
    std::unique_ptr<Background> bg;


    int scrollX, playerX,playerY;
    int scrollY;
    int i;
    Direction currentDir;


public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    StartScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_START_SCENE_H
