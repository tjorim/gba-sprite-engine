//
// Created by Brecht on 6/12/2018.
//

#include "game_scene.h"

#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <math.h>

#include "background.h"
#include "groundbackground.h"
#include "spaceship.h"
#include "level.h"

std::vector<Background *> GameScene::backgrounds() {
    return {
        bg.get(),
        groundBg.get()
    };
}

std::vector<Sprite *> GameScene::sprites() {
    return {
        spaceShipSprite.get()
    };
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spaceshipPal, sizeof(spaceshipPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;

    spaceShipSprite = affineBuilder
            .withData(spaceshipTiles, sizeof(spaceshipTiles))
            .withSize(SIZE_64_64)
            .withAnimated(2, 0)
            .withLocation(0, 0)
            .buildPtr();
    spaceShipSprite->stopAnimating();
    currentFrame = 0;


    bg = std::unique_ptr<Background>(new Background(2, backgroundTiles, sizeof(backgroundTiles), backgroundMap, sizeof(backgroundMap)));
    bg.get()->useMapScreenBlock(16);

    int coordinates [31][2];
    for(int i = 0; i < 31; i++){
        coordinates[i][0] = 8 * i;
        coordinates[i][1] = 144;
    }
    coordinates[0][1] = 128;
    coordinates[1][1] = 136;
    coordinates[2][1] = 128;
    coordinates[3][1] = 120;
    coordinates[4][1] = 128;
    coordinates[5][1] = 136;
    coordinates[6][1] = 144;
    coordinates[7][1] = 156;
    coordinates[8][1] = 164;
    coordinates[9][1] = 156;
    coordinates[10][1] = 144;
    coordinates[11][1] = 156;
    coordinates[12][1] = 156;
    coordinates[13][1] = 144;
    coordinates[14][1] = 144;
    coordinates[15][1] = 144;
    coordinates[16][1] = 144;
    coordinates[17][1] = 144;
    coordinates[18][1] = 144;
    coordinates[19][1] = 136;
    coordinates[20][1] = 128;
    coordinates[21][1] = 120;
    coordinates[22][1] = 112;
    coordinates[23][1] = 104;
    coordinates[24][1] = 96;
    coordinates[25][1] = 88;
    coordinates[26][1] = 80;
    coordinates[27][1] = 72;
    coordinates[28][1] = 80;
    coordinates[29][1] = 88;
    coordinates[30][1] = 96;


    Ground ground = Ground(coordinates, 31);
    SpaceShip spaceShip = SpaceShip(120, 20, 0.1, 0.25, 5);
    level = Level(ground, spaceShip, 100, 140);

    unsigned short groundBackgroundMap [1200];

    for(int i = 0; i < 1200; i++){
        groundBackgroundMap[i] = 0x0000;
    }

    for(int i = 0; i < 30; i++){
        int tileY = coordinates[i][1] / 8 - 2;
        if(coordinates[i][0] >= level.landingBegin && coordinates[i][0] < level.landingEnd){
            groundBackgroundMap[tileY * 32 + i] = 0x0004;
        }
        else if(coordinates[i][1] == coordinates[i + 1][1]){
            groundBackgroundMap[tileY * 32 + i] = 0x0001;
        }
        else if(coordinates[i][1] > coordinates[i + 1][1]){
            groundBackgroundMap[(tileY - 1) * 32 + i] = 0x0003;
        }
        else{
            groundBackgroundMap[tileY * 32 + i] = 0x0002;
        }
    }

    groundBg = std::unique_ptr<Background>(new Background(1, groundBackgroundTiles, sizeof(groundBackgroundTiles), groundBackgroundMap, sizeof(groundBackgroundMap)));
    groundBg.get()->useMapScreenBlock(16);
}

void GameScene::tick(u16 keys) {
    if(keys & KEY_START) {
        level.restart();
        stop = false;
        currentFrame = 0;
        if(!engine->isTransitioning()) {
        }
    } else if(keys & KEY_LEFT) {

    } else if(keys & KEY_RIGHT) {

    } else if(keys & KEY_UP) {

    } else if(keys & KEY_DOWN) {

    }

    level.step();

    if(stop) {
        spaceShipSprite->animateToFrame(0);
    }
    else {
        level.setUp(keys & KEY_UP);
        level.setLeft(keys & KEY_LEFT);
        level.setRight(keys & KEY_RIGHT);

        int frame = 0;

        TextStream::instance().clear();

        if (level.isLanded()) {
            TextStream::instance().setFontColor(0x03E0);
            TextStream::instance() << "Landed";
            stop = true;
        } else if (!level.isAlive()) {
            TextStream::instance().setFontColor(0x001F);
            TextStream::instance() << "Dead";
            stop = true;
        } else {
            spaceShipSprite->rotate((u16) level.getRotation() * 65536 / 360);
            spaceShipSprite->moveTo((int) level.getX() - 32, (int) level.getY() - 32);
            if(keys & KEY_UP){
                frame = 1;
            }
        }
        if(frame != currentFrame){
            spaceShipSprite->animateToFrame(frame);
            currentFrame = frame;
        }
    }
}