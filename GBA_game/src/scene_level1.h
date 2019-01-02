//
// Created by joost on 6/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_PLAY_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_PLAY_SCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "player.h"

class SceneLevel1 : public Scene{
private:
    std::unique_ptr<Player> player;
    std::unique_ptr<AffineSprite> spikeBall;
    std::unique_ptr<AffineSprite> portal;
    std::unique_ptr<Background> bg;
    //std::shared_ptr<Player> player = std::make_shared<Player>(3);

    int hoeveelSpikeBallSpawns, spikeBallSpawn, portalLocation;
    int scrollX, scrollY;
public:

    SceneLevel1(std::shared_ptr<GBAEngine> engine) : Scene(engine), scrollX(0), scrollY(60), hoeveelSpikeBallSpawns(0), spikeBallSpawn(GBA_SCREEN_WIDTH - 100),portalLocation(1000) {}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_PLAY_SCENE_H
