//
// Created by JT
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../thing/bomb.h"

class GameScene : public Scene {
private:
    int level = 1;
    std::vector<std::vector<Thing>> board;
    std::vector<std::unique_ptr<Bomb>> bombs;
    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std::unique_ptr<Sprite> bomSprite;

    std::unique_ptr<Sprite> bompje;

public:
    GameScene(const std::shared_ptr<GBAEngine> &engine, int level);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H