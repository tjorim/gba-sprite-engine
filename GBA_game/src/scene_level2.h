//
// Created by Dominique on 20-Jan-19.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_LEVEL2_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_LEVEL2_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "player.h"

class SceneLevel2 : public Scene{
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<AffineSprite> portal;
    std::unique_ptr<Background> bg;

    u32 portalLocation;
    int scrollX, scrollY;
public:

    SceneLevel2(std::shared_ptr<GBAEngine> engine) : Scene(engine), scrollX(0), scrollY(60), portalLocation(1000) {}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_LEVEL2_H
