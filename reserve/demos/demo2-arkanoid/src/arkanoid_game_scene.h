//
// Created by Wouter Groeneveld on 08/08/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

#include <vector>
#include "balletje.h"

class ArkanoidGameScene : public Scene {
private:
    bool dead;
    int ticks, highscore;

    std::unique_ptr<Sprite> person;
    std::unique_ptr<Sprite> ball;
    std::vector<std::unique_ptr<Balletje>> ballen;
    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std::unique_ptr<Balletje> createBall();

    u32 BallTickCooldown;

    void youDied();
    void resetGame();
    void shoot();

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    ArkanoidGameScene(std::shared_ptr<GBAEngine> engine) : Scene(engine), ticks(0), highscore(0) {}

    void load() override;

    void tick(u16 keys) override;

};






#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_H
