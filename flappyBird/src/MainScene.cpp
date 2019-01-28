//
// Created by Jolien Jeunen on 27/01/2019.
//

#include "MainScene.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "bird1.h"
#include "achtergrondWolkjes.h"
#include "flappybird.h"

double y,x;
int a = 0;

std::vector<Sprite *> MainScene::sprites() {
    return {
        birdSprite.get(),
        buisSprite.get(),
        buisSprite1.get()
        //buisSprite2.get()
    };
}

std::vector<Background *> MainScene::backgrounds() {
    return {
            bg.get()
    };
}

void MainScene::youDied() {
    //if(highscore < ticks) highscore = ticks;
    //engine.get()->enqueueSound(raw_dead, raw_dead_bytes, 32000);
    birdSprite->setVelocity(0, 0);
    if(score > highScore){
        highScore = score;
        TextStream::instance().setText(std::string("je score was: ") + std::to_string(score), 1, 1);
        TextStream::instance().setText(std::string("Nieuwe highscore:") + std::to_string(highScore), 2, 1);
    }else{
        TextStream::instance().setText(std::string("je score was: ") + std::to_string(score) , 1, 1);
        TextStream::instance().setText(std::string("highscore:") + std::to_string(highScore), 2, 1);
    }
    TextStream::instance().setText(std::string("You DIED - start to reset"), 3, 1);
    score = 0;
    //dead = true;
    u16 keys;
    while(!(keys & KEY_START)){
        keys = engine->readKeys();
    }
    resetGame();
}

void MainScene::resetGame() {

    TextStream::instance().clear();
    birdSprite->setVelocity(0, 2);
    birdSprite->moveTo(40, 20);
    buisSprite->moveTo(150, 130);
    buisSprite1->moveTo(250, 100);
}

void MainScene::tick(u16 keys) {
    scrollX += 1;
    if ((birdSprite->collidesWith(*buisSprite)))
    {
        scrollX = 0;
        bg.get()->scroll(scrollX, scrollY);

        youDied();
        return;
    } else if (birdSprite->collidesWith(*buisSprite1)) {

        scrollX = 0;
        bg.get()->scroll(scrollX, scrollY);
        youDied();
        return;

    }


    birdX +=0.3;
    birdY = ((0.05*(birdX*birdX))-3 + birdX);

    if (keys & KEY_A) {
        birdX = -2;
    }

    buisSprite->setStayWithinBounds(false);
    buisSprite1->setStayWithinBounds(false);
    birdSprite->setStayWithinBounds(true);
    buisSprite.get()->moveTo(buisSprite.get()->getX() - 1, buisSprite.get()->getY());
    buisSprite1.get()->moveTo(buisSprite1.get()->getX() - 1, buisSprite1.get()->getY());


    if (buisSprite.get()->getX() <= 0)
    {
        buisSprite.get()->moveTo(250, 130);
        score += 1;
    }

    if (buisSprite1.get()->getX() <= 0)
    {
        buisSprite1.get()->moveTo(300, 110);
        score += 1;
    }

    //score bijhouden

    TextStream::instance().setText(std::string("Score: ") + std::to_string(score), 1, 1);
    birdSprite.get()->setVelocity(0,(int)birdY);
    //birdSprite.get()->rotate((-1024 * ((int)birdY))); // bugt voor een of andere reden, werkt wel in de testgame...
    bg.get()->scroll(scrollX, scrollY);
}

void MainScene::load() {
    score = 0;
    highScore = 0;
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(bird1Pal, sizeof(bird1Pal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(flappybirdPal, sizeof(flappybirdPal)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;

    birdSprite = affineBuilder
            .withData(bird1Tiles, sizeof(bird1Tiles))
            .withSize(SIZE_32_16)
            .withLocation(40, 20)
            .withAnimated(3, 6)
            .withVelocity(0, 2)
            .buildPtr();

    buisSprite = affineBuilder
            .withData(bird1Tiles, sizeof(bird1Tiles))
            .withSize(SIZE_32_64)
            .withLocation(150, 130)
            .withAnimated(4, 6)
            .withVelocity(0, 0)
            .buildPtr();

    buisSprite.get()->stopAnimating();
    buisSprite->animateToFrame(3);

    buisSprite1 = affineBuilder
            .withData(bird1Tiles, sizeof(bird1Tiles))
            .withSize(SIZE_32_64)
            .withLocation(250, 100)
            .withAnimated(4, 6)
            .withVelocity(0, 0)
            .buildPtr();

    buisSprite1.get()->stopAnimating();
    buisSprite1->animateToFrame(3);

    bg = std::unique_ptr<Background>(new Background(1, flappybirdTiles, sizeof(flappybirdTiles), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);
}
