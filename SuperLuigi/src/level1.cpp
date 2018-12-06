//
// Created by Vandebosch Remy on 27/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include "level1.h"
#include "background.h"
#include "Luigi.h"
#include "sharedPal.h"
#include "goomba.h"

std::vector<Background *> level1::backgrounds() {
    return {bg.get()};
}

void level1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager> (new ForegroundPaletteManager(spritesPal, sizeof(spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;

    luigi = affineBuilder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH/2-8, GBA_SCREEN_HEIGHT-45)
            .withAnimated(5,10)
            .buildPtr();
    luigi->stopAnimating();

    goomba = affineBuilder
            .withData(goombaTiles, sizeof(goombaTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH-8, GBA_SCREEN_HEIGHT-45)
            .withAnimated(3,10)
            .buildPtr();
}

std::vector<Sprite *> level1::sprites() {
    return{
        luigi.get(),
        goomba.get()
    };
}

void level1::tick(u16 keys) {

    if(keys & KEY_RIGHT){
        if(luigi->getVelocity().y == 0 && luigi->getCurrentFrame()<4) luigi->animateToFrame(luigi->getCurrentFrame()+1);
        else if (luigi->getVelocity().y == 0)luigi->animateToFrame(0);
        scrollX +=1;
        bg->scroll(scrollX,scrollY);
    }

    if(keys & KEY_UP){
        if(luigi->getY() == GBA_SCREEN_HEIGHT-45) luigi->setVelocity(0,-1);
        luigi->animateToFrame(5);
    }
    else{
        if(luigi->getY() == GBA_SCREEN_HEIGHT-45) {
            luigi->setVelocity(0, 0);
            if(!(keys & KEY_RIGHT)) luigi->animateToFrame(0);
        }
    }
    if(luigi->getY() == GBA_SCREEN_HEIGHT-80) luigi->setVelocity(0,1);
}