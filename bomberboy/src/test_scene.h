//
// Created by JT
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H


#include <libgba-sprite-engine/scene.h>
#include "Models/Dude.h"
#include "Models/BaseData.h"
#include "Models/Bullet.h"
#include "Models/PlayerData.h"
#include "Controllers/PlayerController.h"
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "kul.h"
#include "spritedata.h"

class TestScene : public Scene {
private:
    std::unique_ptr<Sprite> _player;
    std::vector<Sprite*> _bullets;
    std::unique_ptr<Sprite> _bulletSprite;
    PlayerController* _controller;
    Dude* _model;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    TestScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

    void updateFromModel();

};


#endif //GBA_SPRITE_ENGINE_PROJECT_TEST_SCENE_H
