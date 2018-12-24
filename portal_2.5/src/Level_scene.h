//
// Created by Wouter Groeneveld on 02/08/18.
//

#ifndef GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H
#define GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "Portal_bullet.h"
#include "Chell.h"
#include "Level.h"

class Level_scene : public Scene {
private:
    std::unique_ptr<Portal_bullet> redBullet, blueBullet;
    std::unique_ptr<Background> bg;
    std::vector<std::vector<int>> verticalPortalWallCoordinaten = {{232,112},{8,112}};
    std::vector<std::vector<int>>horizontalPortalWallCoordinaten = {{8,144},{40,144},{72,144},{104,144},{136,144},{168,144},{200,144},{8,70},{40,70},{72,70},{136,8},{168,8}};
    std::vector<std::vector<int>>verticalWallCoordinaten = {{240,112},{0,112}};
    std::vector<std::vector<int>> horizontalWallCoordinaten = {{8,152},{40,152},{72,152},{104,152},{136,152},{168,152},{200,152},{8,78},{40,78},{72,78},{136,0},{168,0}};
    int chellX, chellY;
    int visierRotation, jump;
    bool flip_visier;

    Level gameLevel;


public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    Level_scene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void test(Sprite* k);
    void load() override;
    void tick(u16 keys) override;
    void moveChell(u16 keys);
    void checkPortals();

};


#endif //GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H
