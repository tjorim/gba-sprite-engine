//
// Created by Vandebosch Remy on 27/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include <vector>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "Luigi.h"
#include "goomba.h"
#include "QuestionBlock.h"

class level1 : public Scene{
private:
    //the background
    std::unique_ptr<Background> bg;
    std::unique_ptr<Luigi> luigi;
    std::unique_ptr<AffineSprite> luigiSprite;
    std::unique_ptr<Goomba> goomba;
    std::unique_ptr<AffineSprite> goombaSprite;
    std::unique_ptr<QuestionBlock> questionBlock;
    std::unique_ptr<AffineSprite> questionBlockSprite;
    int scrollX, scrollY;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    level1(std::shared_ptr<GBAEngine> engine) : Scene(engine), scrollX(0), scrollY(0) {}

    void load() override;
    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL1_H
