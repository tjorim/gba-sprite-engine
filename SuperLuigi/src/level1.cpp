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
#include "KoopaTiles.h"
#include "Koopa.h"
#include "end_scene.h"
#include <libgba-sprite-engine/effects/fade_out_scene.h>

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
            .withAnimated(5,5)
            .buildPtr();

    luigi = std::unique_ptr<Luigi>{new Luigi(std::move(luigiSprite))};
    luigi->getLuigiSprite()->stopAnimating();
    luigi->setCurrentLvl(1);
    goombaSprite = affineBuilder
            .withData(goombaTiles, sizeof(goombaTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT-bottomHeightFor16)
            .withAnimated(3,5)
            .buildPtr();

    goomba = std::unique_ptr<Goomba>{new Goomba(std::move(goombaSprite))};

    koopaSprite = affineBuilder
            .withData(KoopaTiles, sizeof(KoopaTiles))
            .withSize(SIZE_16_32)
            .withLocation(GBA_SCREEN_WIDTH-10, GBA_SCREEN_HEIGHT-bottomHeightFor32)
            .withAnimated(4,5)
            .buildPtr();

    koopa =std::unique_ptr<Koopa>{new Koopa(std::move(koopaSprite))};
    koopa->getKoopaSprite()->animate();

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
    if(!goomba->isDead() && koopa->isDead())sprites.push_back(goomba->getGoombaSprite().get());
    if(!koopa->isDead() && goomba->isDead()) sprites.push_back(koopa->getKoopaSprite().get());

    return sprites;
}

void level1::addPoint() {
    points++;
    if(points %5 == 0) lives++;
    loadEndScene();
}

void level1::loadEndScene() {
    if(points == 5){
        engine ->transitionIntoScene(new end_scene(engine,points), new FadeOutScene(5));
    }
}

void level1::tick(u16 keys) {
    if(!luigi->isDead() ){
        TextStream::instance().setText("Points: " + std::to_string(points) + " Lives: " + std::to_string(lives) , 0,0);

        koopa->tick(keys);
        goomba->tick(keys);
        questionBlock->tick(keys);
        luigi->tick(keys);

        if((keys & KEY_RIGHT) && !stopScrollBg){
            scrollX +=1;
            bg->scroll(scrollX,scrollY);
        }

        //collision detection between Luigi and goomba or koopa
        if((luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && (luigi->getLuigiSprite()->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) && !goomba->isDead()) ||
            luigi->getLuigiSprite()->collidesWith(*koopa->getKoopaSprite()) && (luigi->getLuigiSprite()->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) && !koopa->isDead()){

            lives--;
            if(lives == 0){
                goomba->getGoombaSprite()->stopAnimating();
                goomba->getGoombaSprite()->setVelocity(0,0);
                koopa->getKoopaSprite()->stopAnimating();
                koopa->getKoopaSprite()->setVelocity(0,0);
                luigi->kill();
                luigi->getLuigiSprite()->stopAnimating();
                luigi->getLuigiSprite()->animateToFrame(0);
            }
            else{
                goomba->getGoombaSprite()->moveTo(goomba->getGoombaSprite()->getX()+50, goomba->getGoombaSprite()->getY());
                koopa->getKoopaSprite()->moveTo(koopa->getKoopaSprite()->getX()+50, koopa->getKoopaSprite()->getY());
            }
        }


        if(luigi->getLuigiSprite()->collidesWith(*goomba->getGoombaSprite()) && luigi->getLuigiSprite()->getVelocity().y > 0 && luigi->getLuigiSprite()->getY()+32 >= GBA_SCREEN_HEIGHT-bottomHeightFor16-14){
            goomba->getGoombaSprite()->stopAnimating();
            goomba->getGoombaSprite()->moveTo(0,0);
            goomba->kill();
            koopa->resurrect();
            luigi->getLuigiSprite()->setVelocity(0,-1);

        }

        if(luigi->getLuigiSprite()->collidesWith(*koopa->getKoopaSprite()) && luigi->getLuigiSprite()->getVelocity().y > 0 && luigi->getLuigiSprite()->getY()+32 >= GBA_SCREEN_HEIGHT-bottomHeightFor32-30){
            koopa->getKoopaSprite()->stopAnimating();
            koopa->getKoopaSprite()->moveTo(0,0);
            koopa->kill();
            goomba->resurrect();
            luigi->getLuigiSprite()->setVelocity(0,-1);

        }

        //collision detection between Luigi and question block
        //vanoder er tegen
        if(luigi->getLuigiSprite()->collidesWith(*questionBlock->getQuestionBlockSprite()) && (luigi->getLuigiSprite()->getVelocity().y < 0) && luigi->getLuigiSprite()->getY() > questionBlock->getQuestionBlockSprite()->getY()+10){
            luigi->getLuigiSprite()->setVelocity(0,1);
            questionBlock->getQuestionBlockSprite()->animateToFrame(2);
            if(!questionBlock->isTriggerd()){
                addPoint();
                questionBlock->trigger();
            }
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
    else{
        TextStream::instance().setText("OH GOD YOU KILLED HIM           YOU MORRON. PRESS CTRL-R TO     TIME TRAVEL", 5,0);
        questionBlock->getQuestionBlockSprite()->setVelocity(0,0);
    }
}