//
// Created by lloyd on 09-Jan-19.
//
#ifndef GBA_SPRITE_ENGINE_PROJECT_CITYSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_CITYSCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>
#include "Direction.h"

#define enemy1X 16
#define enemy1Y 128
#define enemy2X 166
#define enemy2Y 136
//#define enemy3X 144
//#define enemy3Y 174

class CityScene : public Scene {

private:
    std::unique_ptr<Sprite> linkAnimation, sign, apple;
    std::unique_ptr<Sprite> enemy1, enemy2; //, enemy3;
    std::unique_ptr<Sprite> bullet1, bullet2; //, bullet3;
    std::unique_ptr<Background> bg;

    int scrollX,scrollY;
    int playerX,playerY;
    int appleX,appleY;
    int appledx,appledy;
    int appleSpeed;
    int enemy1HP, enemy2HP; //, enemy3HP;
    int bullet1X, bullet1Y;
    int bullet2X, bullet2Y;
    //int bullet3X, bullet3Y;
    int bullet1dx, bullet1dy;
    int bullet2dx, bullet2dy;
    //int bullet3dx, bullet3dy;
    int enemyCD, bulletSpeed;
    int linkHP;

    bool isText;
    bool isNextTileGo;
    Direction currentDir;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    CityScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
    void shoot();
    void enemyshoot(int enemy);
    //bool isNextTileGo(int playerX, int playerY, int scrollX, int scrollY , Direction currentDir);
};
#endif //GBA_SPRITE_ENGINE_PROJECT_CITYSCENE_H
