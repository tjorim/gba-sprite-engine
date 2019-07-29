//
// Created by Wouter Groeneveld on 08/08/18.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <sstream>

#include "arkanoid_game_scene.h"
#include "spritedata.h"
#include "pats.h"
#include "dead.h"

#include "balletje.h"
#include "balletje_data.h"


#define COOLDOWN_BALL_TICK 100




std::vector<Sprite *> ArkanoidGameScene::sprites() {
    std::vector<Sprite*> sprites;

    for(auto& b : ballen) {
        sprites.push_back(b->getSprite());
    }
    sprites.push_back(person.get());
    return sprites;

    /*return {
        paddle.get(), ball.get()
    };*/
}





std::vector<Background *> ArkanoidGameScene::backgrounds() {
    return {};
}

void ArkanoidGameScene::youDied() {
    if(highscore < ticks) highscore = ticks;
    engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
    ball->setVelocity(0, 0);
    TextStream::instance() << "You DIED - start to reset";
    dead = true;
}

void ArkanoidGameScene::resetGame() {
    dead = false;
    ticks = 0;

    TextStream::instance().clear();
    ball->moveTo(110, 140);
    ball->setVelocity(1, 1);
    person->moveTo(100, 150);
}
void ArkanoidGameScene::shoot() {
    int i = 0;
    for(auto& b : ballen) {


        if(  (person->getX() + (person->getWidth()/2 >= b->getSprite()->getX() )&& person->getX() +  (person->getWidth()/2) <= b->getSprite()->getX()+b->getSprite()->getWidth() ) ){
            ballen.erase(ballen.begin()+i);
            return;
        }
        i++;
    }
}

void ArkanoidGameScene::tick(u16 keys) {

    //if(dead) return;

    TextStream::instance().setText(std::string("Ticks: ") + std::to_string(ticks), 5, 10);
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);




    //if(BallTickCooldown > 0) {
    //    BallTickCooldown--;
    //} else if(BallTickCooldown == 0) {
        for(auto &b : ballen) {
            b->tick();
        }
      //  BallTickCooldown = COOLDOWN_BALL_TICK;
    //}



    if(keys & KEY_LEFT) {
        person->setVelocity(-2, 0);
    } else if(keys & KEY_RIGHT) {
        person->setVelocity(+2, 0);
    } else {
        person->setVelocity(0, 0);
    }
    if((keys & KEY_A)) {

            ballen.push_back(createBall());
           // b->setDestination(randomDestinations[rand() % 6]);

    }
    if( keys & KEY_UP) {
        shoot();
    }


}


std::unique_ptr<Balletje> ArkanoidGameScene::createBall() {
    return std::unique_ptr<Balletje>(new Balletje(spriteBuilder->withLocation(50,20).buildWithDataOf(*ball.get()) , 3,1,1 ));

                                                      //withLocation(avatar->getX() + avatar->getWidth() / 2, avatar->getY() + avatar->getHeight() / 2)
                                                      //.buildWithDataOf(*ball.get())));
}




void ArkanoidGameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    SpriteBuilder<Sprite> builder;

    ball = spriteBuilder
            ->withSize(SIZE_8_8)
            .withLocation(110, 140)
            .withData(ballTiles, sizeof(ballTiles))
            .withVelocity(1, 1)
            .buildPtr();


    /*someBulletSprite = spriteBuilder->withData(bullet_data, sizeof(bullet_data))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();
    */

    person = builder
            .withSize(SIZE_32_8)
            .withLocation(100, 150)
            .withData(paddleTiles, sizeof(paddleTiles))
            .withinBounds()
            .buildPtr();



}