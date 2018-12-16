//
// Created by Vandebosch Remy on 27/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "level1.h"
#include "background.h"
#include "Luigi.h"
#include "sharedPal.h"
#include "goomba.h"
#include "music.h"
#include "QuestionBlock.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

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
            .withLocation(GBA_SCREEN_WIDTH/2-8, GBA_SCREEN_HEIGHT-bottomHeightFor32)
            .withAnimated(5,2)
            .buildPtr();
    luigi->stopAnimating();

    goomba = affineBuilder
            .withData(goombaTiles, sizeof(goombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16)
            .withAnimated(3,5)
            .buildPtr();

    questionBlock = affineBuilder
                    .withData(question_blockTiles, sizeof(question_blockTiles))
                    .withSize(SIZE_16_16)
                    .withLocation(GBA_SCREEN_WIDTH/2+10,GBA_SCREEN_HEIGHT-bottomHeightFor32-30)
                    .withAnimated(0,1)
                    .buildPtr();

    engine->enqueueMusic(Tarantella_Napolitana, sizeof(Tarantella_Napolitana));
}

std::vector<Sprite *> level1::sprites() {

    std::vector<Sprite*> sprites;
    sprites.push_back(luigi.get());
    sprites.push_back(questionBlock.get());
    if(!goombaDEAD)sprites.push_back(goomba.get());

    return sprites;
}

void level1::tick(u16 keys) {
    goomba->setVelocity(-1,0);
    questionBlock->setVelocity(0,0);

    if(keys & KEY_RIGHT){
        if(luigi->getVelocity().y == 0) luigi->animate();
        questionBlock-> setVelocity(-1,0);
        scrollX +=1;
        bg->scroll(scrollX,scrollY);
        goomba->setVelocity(goomba->getVelocity().x-1,0);
    }
    else if(luigi->getVelocity().y == 0){

        luigi->stopAnimating();
        luigi->animateToFrame(0);
    }

    if(keys & KEY_UP){

        if(luigi->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) luigi->setVelocity(0,-1);
        luigi->stopAnimating();
        luigi->animateToFrame(5);
    }
    else{

        if(luigi->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) {
            luigi->setVelocity(0, 0);
            if(!(keys & KEY_RIGHT)) luigi->animateToFrame(0);
        }
    }
    if((luigi->getY() == GBA_SCREEN_HEIGHT-120 && luigi->getVelocity().y < 0)
        || (luigi->getY() < GBA_SCREEN_HEIGHT-bottomHeightFor32 && luigi->getVelocity().y == 0)) luigi->setVelocity(0,1);

    if(goomba->getX() <= 0) goomba->moveTo(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16);
    if(questionBlock->getX() <=0) questionBlock->moveTo(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT-bottomHeightFor32-30);

    if(luigi->collidesWith(*goomba) && (luigi->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) && !goombaDEAD){
        TextStream::instance().setText("DEAD", 0,0);
        goomba->stopAnimating();
        goomba->setVelocity(0,0);
    }

    if(luigi ->collidesWith(*questionBlock) && (luigi->getDy() >0) && luigi->getY() > questionBlock->getY()-32) {
        luigi->setVelocity(0,1);
        questionBlock->animateToFrame(2);
    }

    if(luigi->collidesWith(*questionBlock) && luigi->getY() <= questionBlock->getY()-16){
        luigi->setVelocity(0,0);
    }

    if(luigi->collidesWith(*goomba) && luigi->getVelocity().y > 0 && luigi->getY()+32 >= GBA_SCREEN_HEIGHT-bottomHeightFor16){
        goomba->stopAnimating();
        goombaDEAD = true;
    }
}