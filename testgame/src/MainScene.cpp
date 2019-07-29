//
// Created by Jolien Jeunen on 25/01/2019.
//

#include "MainScene.h"
#include "bird1.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <sstream>
//#include "backgroundstuffs.h"

//#include "flappybird.h"
#include "background.h"
#include "fb1MAP.h"
#include <time.h>

std::vector<Sprite *> MainScene::sprites() {
    return{
            //BuisSprite8.get(), // opvulling boven
            //BuisSprite7.get(),
            //BuisSprite6.get(), // opvulling onder
            //BuisSprite5.get(),
            BuisSprite4.get(), // opvulling boven
            BuisSprite3.get(),
            BuisSprite2.get(), // opvulling onder
            BuisSprite1.get(),
            BirdSprite.get()
    };
}

std::vector<Background *> MainScene::backgrounds() {
    return{
            bg.get()
    };
}

void MainScene::load() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(bird1Pal, sizeof(bird1Pal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;


    BirdSprite = affineBuilder
            .withData(bird1Tiles, sizeof(bird1Tiles))
            .withSize(SIZE_32_16)
            .withLocation(40, 20)
            .withAnimated(3,6)
            .withVelocity(0,2)
            .buildPtr();

    BuisSprite1 = builder
            .withData(buisTopTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 0)
            .buildPtr();
    BuisSprite1.get()->stopAnimating();
    BuisSprite1->animateToFrame(0);
    //BuisSprite1.get()->setStayWithinBounds(false);

    BuisSprite2 = builder
            .withData(buisMidTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 0)
            .buildPtr();
    BuisSprite2.get()->stopAnimating();
    BuisSprite2->animateToFrame(0);
    //BuisSprite2.get()->setStayWithinBounds(false);


    BuisSprite3 = builder
            .withData(buisBotTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 16)
            .buildPtr();

    BuisSprite3.get()->stopAnimating();
    BuisSprite3->animateToFrame(0);

    BuisSprite4 = builder
            .withData(buisMidTiles, (sizeof(buisMidTiles)))
            .withSize(SIZE_32_32)
            .withLocation(0, 48)

            .buildPtr();
    BuisSprite4.get()->stopAnimating();
    BuisSprite4->animateToFrame(0);
    //BuisSprite4.get()->setStayWithinBounds(false);

    BuisSprite5 = builder
            .withData(buisTopTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 0)
            .buildPtr();
    BuisSprite5.get()->stopAnimating();
    BuisSprite5->animateToFrame(0);
    //BuisSprite1.get()->setStayWithinBounds(false);

    BuisSprite6 = builder
            .withData(buisMidTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 0)
            .buildPtr();
    BuisSprite6.get()->stopAnimating();
    BuisSprite6->animateToFrame(0);
    //BuisSprite2.get()->setStayWithinBounds(false);


    BuisSprite7 = builder
            .withData(buisBotTiles, sizeof(buisBotTiles))
            .withSize(SIZE_32_32)
            .withLocation(0, 16)
            .buildPtr();

    BuisSprite7.get()->stopAnimating();
    BuisSprite7->animateToFrame(0);

    BuisSprite8 = builder
            .withData(buisMidTiles, (sizeof(buisMidTiles)))
            .withSize(SIZE_32_32)
            .withLocation(0, 96)

            .buildPtr();
    BuisSprite8.get()->stopAnimating();
    BuisSprite8->animateToFrame(0);
    //BuisSprite4.get()->setStayWithinBounds(false);


    scrollBuisX = 256;
    BuisSprite8.get()->setStayWithinBounds(false);
    BuisSprite7.get()->setStayWithinBounds(false);
    BuisSprite6.get()->setStayWithinBounds(false);
    BuisSprite5.get()->setStayWithinBounds(false);
    BuisSprite4.get()->setStayWithinBounds(false);
    BuisSprite3.get()->setStayWithinBounds(false);
    BuisSprite2.get()->setStayWithinBounds(false);
    BuisSprite1.get()->setStayWithinBounds(false);
    srand (time(NULL));
    scrollBuisY = 63;
    //TextStream::instance() <<"Werkt deze shizzle?" << "How jong.";


    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);
}

void MainScene::tick(u16 keys) {

    int y; // waarde voor de afstand vd buizen
    birdX+=0.3;

    birdY= ((0.05*(birdX*birdX))-3 + birdX);
    scrollX += 1;
    if(scrollBuisX < -32){
        scrollBuisX = 256;
        scrollBuisY = (rand() % 64)+32; //genereer een getal tss 32-96
    }else{
        scrollBuisX -= 1;

    }
    y = scrollBuisY;


    BuisSprite1.get()->moveTo(scrollBuisX,32+y);
    if(y+64 >= 128){
        BuisSprite2.get()->moveTo(scrollBuisX,0);
    }else{
        BuisSprite2.get()->moveTo(scrollBuisX,y+64+32);
    }

    BuisSprite3.get()->moveTo(scrollBuisX,y-32-32);
    if(y-64 <= 0){
        BuisSprite4.get()->moveTo(scrollBuisX,128);
    }else{
        BuisSprite4.get()->moveTo(scrollBuisX,y-64-32);
    }

    if(keys & KEY_A){
        birdX = -2;
    }
/*
    BuisSprite5.get()->moveTo(scrollBuisX+100,32+y);
    if(64+y > 128){
        BuisSprite6.get()->moveTo(scrollBuisX+100,64+y-128);
    }else{
        BuisSprite6.get()->moveTo(scrollBuisX+100,64+y);
    }
    BuisSprite7.get()->moveTo(scrollBuisX+100,y-32-32);
    if(y-64-32 < 128){
        BuisSprite8.get()->moveTo(scrollBuisX+100,y-64-32+128);
    }else{
        BuisSprite8.get()->moveTo(scrollBuisX+100,y-64-32+128);
    }
*/
    if(keys & KEY_A){
        birdX = -2;
    }

    BirdSprite.get()->setVelocity(0,(int)birdY);

    TextStream::instance().setText(std::string("test: ") + std::to_string(y), 1, 1);
    BirdSprite.get()->rotate(-1024 * (int)birdY);

    bg.get()->scroll(scrollX, scrollY);

    /** CODE OM POPPETJE TE LATEN BEWEGEN EN TERUG TE LATEN BOTSEN BIJ DE RANDEN**/

    /*if(mooimanSprite->getX() <= 0 || mooimanSprite->getX() >= (GBA_SCREEN_WIDTH - mooimanSprite->getWidth()))
    {
        mooimanSprite->setVelocity(-mooimanSprite->getDx(), mooimanSprite->getDy());
    }
    else if(mooimanSprite->getY() <= 0)
    {
        mooimanSprite->setVelocity(mooimanSprite->getDx(), -mooimanSprite->getDy());
    }
    else if(mooimanSprite->getY() >= (GBA_SCREEN_HEIGHT - mooimanSprite->getHeight()))
    {
        mooimanSprite->setVelocity(mooimanSprite->getDx(), -mooimanSprite->getDy());
    }
    else if(mooimanSprite->collidesWith(*paddle))
    {
        if(ticks > 1 && ticks % 5 == 0)
        {
            mooimanSprite->setVelocity(mooimanSprite->getDx() + 1, mooimanSprite->getDy() + 1);
        }

        // lousy implementation; mooimanSprite could also hit paddle from right/left, meaning *BOOM*
        mooimanSprite->setVelocity(mooimanSprite->getDx(), -mooimanSprite->getDy());
        engine.get()->enqueueSound(pats, sizeof(pats), 32000);

        ticks++;
    }*/

    /*if(keys & KEY_LEFT) {
        mooimanSprite->setVelocity(-1, 0);
    } else if(keys & KEY_RIGHT) {
        mooimanSprite->setVelocity(+1, 0);
    } else if(keys & KEY_UP) {
        mooimanSprite->setVelocity(0, -1);
    } else if(keys & KEY_DOWN) {
        mooimanSprite->setVelocity(0, +1);
    } else {
        mooimanSprite->setVelocity(0, 0);
    }*/
}