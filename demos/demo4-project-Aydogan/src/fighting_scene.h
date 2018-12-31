//
// Created by aydoganmusa on 22.11.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>
#include "Goku.h"
#include "Yamcha.h"

class FightingScene : public Scene {
private:
    std::unique_ptr<Sprite> goku;
    std::unique_ptr<Sprite> lifebar_goku;
    std::unique_ptr<Sprite> energybar_goku;
    std::unique_ptr<Sprite> wave;
    std::unique_ptr<Goku> goku_object;
    std::unique_ptr<Sprite> yamcha;
    std::unique_ptr<Sprite> lifebar_yamcha;
    std::unique_ptr<Sprite> energybar_yamcha;
    std::unique_ptr<Yamcha> yamcha_object;
    std::unique_ptr<Background> bg;

    bool gameEnd = false;

public:
    FightingScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 i) override;

    void resetGame();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_FIGHTING_SCENE_H
