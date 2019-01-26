//
// Created by Wouter Groeneveld on 08/08/18.
//
#define NUM_OF_BALLS 2

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "arkanoid_game_scene.h"
#include "spritedata.h"
#include "pats.h"
#include "dead.h"

std::vector<Sprite *> ArkanoidGameScene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(paddle.get());
    for (int i = 0; i < NUM_OF_BALLS; ++i) {
        sprites.push_back(ball[i].get());
    }
    return sprites;
}

std::vector<Background *> ArkanoidGameScene::backgrounds() {
    return {};
}

void ArkanoidGameScene::youDied() {
    if(highscore < ticks) highscore = ticks;
    engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
    for(int i = 0; i < NUM_OF_BALLS; ++i) {
        ball[i]->setVelocity(i % 5 + 1, i % 5 + 1); 
    }
    
    TextStream::instance() << "You DIED - start to reset";
    dead = true;
}

void ArkanoidGameScene::resetGame() {
    if(highscore < ticks) highscore = ticks;

    dead = false;
    ticks = 0;

    TextStream::instance().clear();
    for(int i = 0; i < NUM_OF_BALLS; ++i) {
        ball[i]->moveTo(110, 140);
        ball[i]->setVelocity(i % 5 + 1, i % 5 + 1);
    }
    
    paddle->moveTo(100, 150);
}

void ArkanoidGameScene::ballTick(Sprite* paddle, Sprite* ball) {
    // If the ball hits the paddle from the side
    // if(ball->getDy()<=paddle->getDy()) {
    //     ball->setVelocity(-ball->getDx(), -ball->getDy());  
    // } else {
    //     ball->setVelocity(ball->getDx(), -ball->getDy());  
    // }
    ball->setVelocity(ball->getDx(), -ball->getDy());
}

void ArkanoidGameScene::tick(u16 keys) {
    // if(dead && (keys & KEY_START)) {
    //     resetGame();
    //     return;
    // }

    // if(dead) return;

    TextStream::instance().setText(std::string("Ticks: ") + std::to_string(ticks), 5, 10);
    TextStream::instance().setText(std::string("Highscore: ") + std::to_string(highscore), 7, 10);

    for(int i = 0; i < NUM_OF_BALLS; ++i) {
        if(ball[i]->getX() <= 0 || ball[i]->getX() >= (GBA_SCREEN_WIDTH - ball[i]->getWidth())) {
            ball[i]->setVelocity(-ball[i]->getDx(), ball[i]->getDy());
        }else if(ball[i]->getY() <= 0) {
            ball[i]->setVelocity(ball[i]->getDx(), -ball[i]->getDy());
        } else if(ball[i]->getY() >= (GBA_SCREEN_HEIGHT - ball[i]->getHeight())) {
            ball[i]->setVelocity(ball[i]->getDx(), -ball[i]->getDy());
            //youDied();
           //return;
        } else if(ball[i]->collidesWith(*paddle)) {
            if(ticks > 1 && ticks % 5 == 0) {
                ball[i]->setVelocity(ball[i]->getDx() + 1, ball[i]->getDy() + 1);
            }
            //ballTick(ball[i].get(), paddle.get());
            // lousy implementation; ball could also hit paddle from right/left, meaning *BOOM*
            if(ball[i]->getDy() <= paddle->getDy() + paddle->getHeight()) {
                ball[i]->setVelocity(-ball[i]->getDx(), -ball[i]->getDy());
            } else {
                ball[i]->setVelocity(ball[i]->getDx(), -ball[i]->getDy());
            }
            
            engine.get()->enqueueSound(pats, sizeof(pats), 32000);

            ticks++;
        }
    }
    

    if(keys & KEY_LEFT) {
        paddle->setVelocity(-5, 0);
    } else if(keys & KEY_RIGHT) {
        paddle->setVelocity(+5, 0);
    } else {
        paddle->setVelocity(0, 0);
    }

    if(keys & KEY_START) {
        resetGame();
    }
}

void ArkanoidGameScene::load() {
    engine.get()->enableText();
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));

    SpriteBuilder<Sprite> builder;

    ball = new std::unique_ptr<Sprite>[NUM_OF_BALLS];

    for (int i = 0; i < NUM_OF_BALLS; ++i) {
        ball[i] = builder
            .withSize(SIZE_8_8)
            .withLocation(110, 140)
            .withData(ballTiles, sizeof(ballTiles))
            .withVelocity(1, 1)
            .buildPtr();
    }
    

    paddle = builder
            .withSize(SIZE_32_8)
            .withLocation(100, 150)
            .withData(paddleTiles, sizeof(paddleTiles))
            .withinBounds()
            .buildPtr();
}