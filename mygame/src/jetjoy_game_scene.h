//
// Created by Ruben Ponsaers on 30/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include "ship.h"

class JetjoyGameScene : public Scene{
private:
    std::unique_ptr<Ship> ship;
    std::unique_ptr<AffineSprite> shipSprite;
    std::unique_ptr<Background> background;

public:
    JetjoyGameScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_JETJOY_GAME_SCENE_H
