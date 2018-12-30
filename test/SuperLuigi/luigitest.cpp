//
// Created by Vandebosch Remy on 25/12/2018.
//

#include <gtest/gtest.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "../../SuperLuigi/src/Luigi.h"
#include "../../SuperLuigi/src/Luigi.h"
#include "../../SuperLuigi/src/LuigiTiles.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

class LuigiTestObject : public :: testing::Test{
protected:
    std::unique_ptr<AffineSprite> luigiSprite;
    std::unique_ptr<Luigi> luigi;

    virtual void TearDown(){

    }

    virtual  void SetUp(){
        SpriteBuilder<AffineSprite> affineBuilder;

        luigiSprite = affineBuilder
                .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
                .withSize(SIZE_16_32)
                .withLocation(GBA_SCREEN_WIDTH/2-8, GBA_SCREEN_HEIGHT-bottomHeightFor32)
                .withAnimated(5,2)
                .buildPtr();

        luigi = std::unique_ptr<Luigi>{new Luigi(std::move(luigiSprite))};
    }
};

TEST_F(LuigiTestObject, luigiJumpTest){
    luigi->tick(KEY_UP);

    ASSERT_FALSE(luigi->getLuigiSprite()->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32);
}