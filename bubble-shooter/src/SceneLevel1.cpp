//
// Created by 11401165 on 29/11/2018. TEST TEST
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <sstream>

#include "SceneLevel1.h"


#define MAXBULLETS 10
#define BULLET_COOLDOWN_START 10
#define ERASE_NOTHING  -1

void SceneLevel1:: bulletDelete(){

    int eraseBullet = bulletOffScreen();

    if( eraseBullet != ERASE_NOTHING ){
        bulletCooldown +=5;
        bullets.erase(bullets.begin()+ eraseBullet);
    }
    return;
}

int SceneLevel1:: bulletOffScreen(){

    int bulletCnt = 0;
    for(auto &b : bullets) {

        if(b.get()->isOffScreen() || b->getY() == 0){
            return bulletCnt;
        }
        bulletCnt++;
    }
    return ERASE_NOTHING;
}

void SceneLevel1::ballHitPerson(){

    for(auto &b : ballen) {
        if(b.get()->getSprite()->collidesWith(*person.get())){
            dead();
        }
    }

}

void SceneLevel1:: dead(){
    TextStream::instance().setText(std::string("You are dead! Je kan er niets meer aan doen!"), 9, 0);
    while(1){}
}

int SceneLevel1:: bulletCollidesBall(){

    for(auto &bul : bullets){
            int balCnt = 0;
            for(auto &bal : ballen){
                if( bul.get()->collidesWith(*bal->getSprite())){
                    score++;
                    if( bal->getNumber() !=  BALLKLEIN){
                        ballen.push_back(createBall( (bal->getNumber()-1),LEFT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                        ballen.push_back(createBall( (bal->getNumber()-1),RIGHT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                    }
                    bul->moveTo(-100,-100);
                    return balCnt;
                }
                balCnt++;
            }
    }

    return ERASE_NOTHING;
}

void SceneLevel1:: checkBulletHitBall(){

    int numberBulletErase = bulletCollidesBall();

    if( numberBulletErase != ERASE_NOTHING){
        ballen.erase(ballen.begin()+ numberBulletErase);
    }

}

std::vector<Sprite *> SceneLevel1::sprites() {
    std::vector<Sprite*> sprites;

    for(auto& b : ballen) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : bullets) {
        sprites.push_back(b.get());
    }

    sprites.push_back(ballSmall.get());
    sprites.push_back(ballBig.get());
    sprites.push_back(ballMedium.get());
    sprites.push_back(bullet.get());
    sprites.push_back(person.get());
    return sprites;

}

std::vector<Background *> SceneLevel1::backgrounds() {
    return {
            bg.get()
    };
}


std::unique_ptr<Ball> SceneLevel1::createBall(int ballType, int dx, int dy,int posX, int posY) {

    if( ballType == BALLKLEIN){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*ballSmall.get()) , BALLKLEIN,dx,dy ));
    }
    else if(ballType == BALLMIDDEL){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*ballMedium.get()) , BALLMIDDEL,dx,dy ));
    }
    else if(ballType == BALLGROOT){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*ballBig.get()) , BALLGROOT,dx,dy ));
    }
    else{
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*ballBig.get()) , BALLGROOT,dx,dy ));
    }

}

std::unique_ptr<Sprite> SceneLevel1::createBullet(){
    return  spriteBuilderBullet->withLocation((person.get()->getX() + (person.get()->getWidth())/2 - (bullet.get()->getWidth()/2)) , (GBA_SCREEN_HEIGHT-person.get()->getHeight()-bullet.get()->getHeight())).withVelocity(0,-5).buildWithDataOf(*bullet.get());
}

void SceneLevel1::loadAlways() {

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal,sizeof(sharedPal)));
    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    spriteBuilderBullet = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    SpriteBuilder<Sprite> builder;

    ballBig = spriteBuilder
            ->withData(ball32Tiles, sizeof(ball32Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-10, -10)
            .buildPtr();

    ballMedium = spriteBuilder
            ->withData(ball16Tiles, sizeof(ball16Tiles))
            .withSize(SIZE_16_16)
            .withLocation(-10, -10)
            .buildPtr();

    ballSmall = spriteBuilder
            ->withData(ball8Tiles, sizeof(ball8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(-10, -10)
            .buildPtr();

    bullet = spriteBuilderBullet
            ->withData(bullet8Tiles, sizeof(bullet8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(-10, -10)
            .buildPtr();

    person = spriteBuilder
            ->withData(man1616_v1Tiles, sizeof(man1616_v1Tiles))
            .withSize(SIZE_16_16)
            .withLocation(50, GBA_SCREEN_HEIGHT-16)
            .buildPtr();
}
void SceneLevel1:: text(){
    TextStream::instance().setText(std::string("Score: ")+ std::to_string(score), 0, 0);
    TextStream::instance().setText(std::string("Bullet cooldwn: ")+ std::to_string(bulletCooldown), 5, 0);
    TextStream::instance().setText(std::string("Ballen: ")+ std::to_string(ballen.size()), 6, 0);
    TextStream::instance().setText(std::string("Bullets: ")+ std::to_string(bullets.size()), 7, 0);
}

void SceneLevel1:: movePerson(u16 keys) {

    if(keys & KEY_LEFT) {

        person->setVelocity(-2, 0);
        scrollX++;
        bg.get()->scroll(scrollX,0);

    } else if(keys & KEY_RIGHT) {

        person->setVelocity(+2, 0);
        scrollX--;
        bg.get()->scroll(scrollX,0);

    } else {
        person->setVelocity(0, 0);
    }

}

void SceneLevel1:: tickAlways(u16 keys){
    text();
    if((keys & KEY_A)) {
         ballen.clear();
    }

    bool allowedToShoot = false;

    if(bulletCooldown > 0) {
        bulletCooldown--;

    } else if(bulletCooldown == 0) {
        allowedToShoot = true;
    }

    if( keys & KEY_UP && bullets.size()< MAXBULLETS & allowedToShoot) {
        bulletCooldown = BULLET_COOLDOWN_START;
        bullets.push_back(createBullet());

    }

    if(game < GAMESTARTED){
        atStartGame();
        game++;
    }

    movePerson(keys);
    bulletDelete();
    checkBulletHitBall();
    ballHitPerson();
    for(auto &b : ballen) {
        b->tick();
    }

}

