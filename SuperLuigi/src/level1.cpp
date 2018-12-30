//
// Created by Vandebosch Remy on 27/11/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "level1.h"
#include "background.h"
#include "LuigiTiles.h"
#include "sharedPal.h"
#include "goombaTiles.h"
#include "music.h"
#include "QuestionBlockTiles.h"
#include "Luigi.h"
#include "goomba.h"
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

    SpriteBuilder<AffineSprite> affineBuilder;

    luigiSprite = affineBuilder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH/2-8, GBA_SCREEN_HEIGHT-bottomHeightFor32)
            .withAnimated(5,2)
            .buildPtr();

    luigi = std::unique_ptr<Luigi>{new Luigi(std::move(luigiSprite))};
    luigi->getLuigiSprite()->stopAnimating();

    goombaSprite = affineBuilder
            .withData(goombaTiles, sizeof(goombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16)
            .withAnimated(3,5)
            .buildPtr();

    goomba = std::unique_ptr<Goomba>{new Goomba(std::move(goombaSprite))};


    questionBlockSprite = affineBuilder
                    .withData(question_blockTiles, sizeof(question_blockTiles))
                    .withSize(SIZE_16_16)
                    .withLocation(GBA_SCREEN_WIDTH/2+10,GBA_SCREEN_HEIGHT-bottomHeightFor32-30)
                    .withAnimated(0,1)
                    .buildPtr();

    questionBlock = std::unique_ptr<QuestionBlock>{new QuestionBlock(std::move(questionBlockSprite))};

    engine->enqueueMusic(Tarantella_Napolitana, sizeof(Tarantella_Napolitana));
}

std::vector<Sprite *> level1::sprites() {

    std::vector<Sprite*> sprites;
    sprites.push_back(luigi->getLuigiSprite().get());
    sprites.push_back(questionBlock->getQuestionBlockSprite().get());
    if(!goomba->isDead())sprites.push_back(goomba->getGoombaSprite().get());

    return sprites;
}

void level1::tick(u16 keys) {
    if(!luigi->isDead()){
        goomba->tick(keys);
        questionBlock->tick(keys);
        luigi->tick(keys);

        if((keys & KEY_RIGHT) && !stopScrollBg){
            scrollX +=1;
            bg->scroll(scrollX,scrollY);
        }

        //collision detection between Luigi and goomba
        if(luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && (luigi->getLuigiSprite()->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) && !goomba->isDead()){
            TextStream::instance().setText("OH GOD YOU KILLED HIM           YOU MORRON. PRESS CTRL-R TO     TIME TRAVEL", 5,0);
            goomba->getGoombaSprite()->stopAnimating();
            goomba->getGoombaSprite()->setVelocity(0,0);
            luigi->kill();
            luigi->getLuigiSprite()->stopAnimating();
            luigi->getLuigiSprite()->animateToFrame(0);
        }


        if(luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && luigi->getLuigiSprite()->getVelocity().y > 0 && luigi->getLuigiSprite()->getY()+32 >= GBA_SCREEN_HEIGHT-bottomHeightFor16){
            goomba->getGoombaSprite()->stopAnimating();
            goomba->getGoombaSprite()->moveTo(0,0);
            goomba->kill();
            luigi->getLuigiSprite()->setVelocity(0,-1);
            questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
        }

        //collision detection between Luigi and question block
        //vanoder er tegen
        if(luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite()) && (luigi->getLuigiSprite()->getVelocity().y < 0) && luigi->getLuigiSprite()->getY() > questionBlock->getQuestionBlockSprite()->getY()+10){
            luigi->getLuigiSprite()->setVelocity(0,1);
            questionBlock->getQuestionBlockSprite()->animateToFrame(2);
        }

        //er tegen langs zijkanten
        if(luigi->getLuigiSprite()->getX()+10 <= questionBlock->getQuestionBlockSprite()->getX() && luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite())){
            questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
            luigi->getLuigiSprite()->setVelocity(0,1);
            stopScrollBg = true;
        } else stopScrollBg = false;

        //erop
        if(luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite()) && luigi->getLuigiSprite()->getY() < (questionBlock->getQuestionBlockSprite()->getY()-30)
           && luigi->getLuigiSprite()->getX()+8 > questionBlock->getQuestionBlockSprite()->getX()){
            luigi->getLuigiSprite()->setVelocity(0,0);
        }

    }
}