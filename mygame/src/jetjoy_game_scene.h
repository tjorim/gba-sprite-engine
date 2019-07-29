//
// Created by Ruben Ponsaers on 30/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include "ship.h"
#include "ghost.h"
#include "laser.h"

class JetjoyGameScene : public Scene{
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Ship> ship;
    std::unique_ptr<AffineSprite> shipSprite;
    std::unique_ptr<Ghost> ghost;
    std::unique_ptr<AffineSprite> ghostSprite;
    std::unique_ptr<Laser> laser;
    std::unique_ptr<AffineSprite> laserSprite;
    int score;
    bool nextlevel;


public:
    JetjoyGameScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
    void endgame();
    void scoreHandler();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H
