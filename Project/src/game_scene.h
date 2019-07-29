//
// Created by Brecht on 6/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>

#include <vector>
#include "level.h"

class GameScene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Background> groundBg;
    std::unique_ptr<AffineSprite> spaceShipSprite;
    Level level;
    bool stop;
    int currentFrame;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    GameScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H
