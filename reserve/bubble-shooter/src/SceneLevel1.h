//
// Created by 11401165 on 29/11/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h> // niet perse nodig

#include <vector>
#include "Ball.h"





class SceneLevel1: public Scene {

private:

    int score;
    std:: unique_ptr<Sprite> BallBig;
    std:: unique_ptr<Sprite> BallMedium;
    std:: unique_ptr<Sprite> BallSmall;
    std:: unique_ptr<Sprite> Person;
    std:: unique_ptr<Sprite> Bullet;




    std::vector<std::unique_ptr<Ball>> ballen;
    std::vector<std::unique_ptr<Sprite>> bullets;

    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std::unique_ptr<Ball> createBall(int number, int dx, int dy,int posX, int posY);
    std::unique_ptr<Sprite> createBullet();
    void shoot();
    void bullet_offScreen();
    void bullet_hit_ball();
    void personHit();
    void ball_hit_person();
    void dead();

    //void copy_vector(std::vector<Ball> copied_in, std::vector<Ball> ball_to_copy);



public:
    SceneLevel1(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENELEVEL1_H