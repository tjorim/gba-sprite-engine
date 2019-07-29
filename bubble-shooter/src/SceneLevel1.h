//
// Created by 11401165 on 29/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h> // niet perse nodig // background
#include <libgba-sprite-engine/background/background.h> // background
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <vector>
#include "Ball.h"

#define BALLKLEIN		 0
#define BALLMIDDEL		 1
#define BALLGROOT		 2

#define LEFT -1
#define RIGHT 1
#define UP -1
#define Down 1

#define GAMESTARTED 1
#include "sprites_front.h"
#include "background.h"
#include "Ball.h"



class SceneLevel1: public Scene {
private:
    int bulletOffScreen();
    int bulletCollidesBall();
    void bulletDelete();
    void checkBulletHitBall();
    void ballHitPerson();
    void dead();



public:
    int scrollX=0;
    std:: unique_ptr<Sprite> person;
    std:: unique_ptr<Sprite> ballBig;
    std:: unique_ptr<Sprite> ballMedium;
    std:: unique_ptr<Sprite> ballSmall;
    std:: unique_ptr<Sprite> bullet;

    bool personAllowed2Move = true;

    //virtual void movePerson(int direction);
    virtual void movePerson(u16 keys);
    SceneLevel1(std::shared_ptr<GBAEngine> engine, int start_score) : Scene(engine), score(start_score) {}
    void loadAlways();
    void tickAlways(u16 keys);
    int game = 0;
    u32 bulletCooldown = 0;
    int score = 0;

    std:: unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std:: unique_ptr<SpriteBuilder<Sprite>> spriteBuilderBullet;
    std:: unique_ptr<Ball> createBall(int ballType, int dx, int dy,int posX, int posY);
    std:: unique_ptr<Sprite> createBullet();



    std::unique_ptr<Background> bg;
    std::vector<std::unique_ptr<Ball>> ballen;
    std::vector<std::unique_ptr<Sprite>> bullets;
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;



    void text();

    virtual void atStartGame() = 0;



};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H