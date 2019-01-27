//
// Created by mathi on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_END_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_END_SCENE_H
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "Luigi.h"
#include "bowser.h"
#include "goomba.h"
#include "QuestionBlock.h"
#include "Koopa.h"


class end_scene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Luigi> luigi;
    std::unique_ptr<bowser> Bowser;
    std::unique_ptr<AffineSprite> luigiSprite;
    std::unique_ptr<AffineSprite> bowserSprite;
    int points;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    end_scene(std::shared_ptr<GBAEngine> engine, int p) : Scene(engine), points(p) {}
    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_END_SCENE_H
