//
// Created by 11401165 on 29/11/2018.
//
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include <libgba-sprite-engine/gba_engine.h>
#include <algorithm>
#include <sstream>

#include "SceneLevel1.h"
#include "sprites_front.h"
#include "Ball.h"

#define MAXBULLETS 2


#define BALLKLEIN		 0
#define BALLMIDDEL		 1
#define BALLGROOT		 2

#define LEFT -1
#define RIGHT 1
#define UP -1
#define Down 1



#define StartGame 1
int Game = 0;

void SceneLevel1:: bullet_offScreen(){
    int i = 0;
    for(auto &b : bullets) {

        if(b.get()->isOffScreen()){
            bullets.erase(bullets.begin()+i);
            return;
        }
        i++;
    }
}



void SceneLevel1::ball_hit_person(){
    int i = 0;
    for(auto &b : ballen) {

        if(b.get()->getSprite()->collidesWith(*Person.get())){
            dead();
        }
        i++;
    }
}

void SceneLevel1:: dead(){
    TextStream::instance().setText(std::string("You are dead!"), 5, 10);

    while(1){}

}


/*void SceneLevel1:: copy_vector(std::vector<Ball> copied_in, std::vector<Ball> ball_to_copy) {

    copied_in.clear();
    for (int i = 0; i < ball_to_copy.size(); i++){
        copied_in.push_back(ball_to_copy[i]);
    }
    return;
}*/


void SceneLevel1:: bullet_hit_ball(){
    int i = 0;

    std::vector<std::unique_ptr<Ball>> ballen_temp;
    //std::vector<Ball> ballen_temp;
    //std::vector<Ball> ballen1;
    //copy_vector(ballen_temp,ballen);

    //std::copy(ballen.begin(),ballen.end(),std::back_inserter(ballen_temp));
    //ballen_temp.reserve(ballen.size());
    //std::copy(ballen1.begin(),ballen1.end(),std::back_inserter(ballen_temp));

   // std::copy(ballen.begin(),ballen.end(),std::back_inserter(ballen_temp));

    //std::vector<std::unique_ptr<Sprite>> bullets_temp;
    //bullets_temp.reserve(bullets.size());
    //copy(bullets.begin(),bullets.end(),back_inserter(bullets_temp));


    std::vector<Ball> from_vector;
    //std::iota(from_vector.begin(), from_vector.end(), 0);

    std::vector<Ball> to_vector;
    std::copy(from_vector.begin(), from_vector.end(),
              std::back_inserter(to_vector));

    for(auto &bul : bullets) {
        int y = 0;


        for(auto &bal : ballen){


            if( bul.get()->collidesWith(*bal->getSprite())){
                score++;
                TextStream::instance().setText(std::string("Score: ")+ std::to_string(score), 0, 0);

                if( bal->getNumber() !=  BALLKLEIN){
                    //ballen.push_back(createBall( (BALLKLEIN),LEFT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                    ballen.push_back(createBall( (bal->getNumber()-1),LEFT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                    ballen.push_back(createBall( (bal->getNumber()-1),RIGHT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));

                    //ballen_temp.push_back(createBall( (bal->getNumber()-1),LEFT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                    //ballen_temp.push_back(createBall( (bal->getNumber()-1),RIGHT,UP,bal->getSprite()->getX(),bal->getSprite()->getY()));
                }

               //ballen.push_back(createBall(BALLKLEIN,1,-1,30,60));


                //ballen_temp.erase(ballen_temp.begin()+y);
                //bullets_temp.erase(bullets_temp.begin()+y);

                bullets.erase(bullets.begin()+i);
                ballen.erase(ballen.begin()+y);



                //return;
            }
            y++;
        }
        i++;
    }
    //copy(ballen.begin(),ballen.end(),back_inserter(ballen_temp));
    //copy(bullets.begin(),bullets.end(),back_inserter(bullets_temp));

}


std::vector<Sprite *> SceneLevel1::sprites() {
    std::vector<Sprite*> sprites;

    for(auto& b : ballen) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : bullets) {
        sprites.push_back(b.get());
    }


    sprites.push_back(BallSmall.get());
    sprites.push_back(BallBig.get());
    sprites.push_back(BallMedium.get());
    sprites.push_back(Bullet.get());
    sprites.push_back(Person.get());
    return sprites;

}

std::vector<Background *> SceneLevel1::backgrounds() {
    return {};
}


std::unique_ptr<Ball> SceneLevel1::createBall(int number, int dx, int dy,int posX, int posY) {
    if( number == BALLKLEIN){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*BallSmall.get()) , BALLKLEIN,dx,dy ));
    }else if(number == BALLMIDDEL){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*BallMedium.get()) , BALLMIDDEL,dx,dy ));
    }
    else if(number == BALLGROOT){
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*BallBig.get()) , BALLGROOT,dx,dy ));
    }
    else{
        return std::unique_ptr<Ball>(new Ball(spriteBuilder->withLocation(posX,posY).buildWithDataOf(*BallBig.get()) , 0,dx,dy ));
    }
    //withLocation(avatar->getX() + avatar->getWidth() / 2, avatar->getY() + avatar->getHeight() / 2)
    //.buildWithDataOf(*ball.get())));
}

std::unique_ptr<Sprite> SceneLevel1::createBullet(){

    return  spriteBuilder->withLocation((Person.get()->getX() + (Person.get()->getWidth())/2 - (Bullet.get()->getWidth()/2)) , (GBA_SCREEN_HEIGHT-Person.get()->getHeight()-Bullet.get()->getHeight())).withVelocity(0,-5).buildWithDataOf(*Bullet.get());
}




void SceneLevel1::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal,sizeof(sharedPal)));
    backgroundPalette = std:: unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    SpriteBuilder<Sprite> builder;

    BallBig = spriteBuilder
            ->withData(ball32Tiles, sizeof(ball32Tiles))
            .withSize(SIZE_32_32)
            .withLocation(-10, -10)
            .buildPtr();

    BallMedium = spriteBuilder
            ->withData(ball16Tiles, sizeof(ball16Tiles))
            .withSize(SIZE_16_16)
            .withLocation(-10, -10)
            .buildPtr();

    BallSmall = spriteBuilder
            ->withData(ball8Tiles, sizeof(ball8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(-10, -10)
            .buildPtr();

    Bullet = spriteBuilder
            ->withData(bullet8Tiles, sizeof(bullet8Tiles))
            .withSize(SIZE_8_8)
            .withLocation(-10, -10)
            .buildPtr();

    //->withData(man1632Tiles, sizeof(man1632Tiles)) man1616_v1Tiles
    Person = spriteBuilder
            ->withData(man1616_v1Tiles, sizeof(man1616_v1Tiles))
            .withSize(SIZE_16_16)
            .withLocation(150, GBA_SCREEN_HEIGHT-16)
            .buildPtr();


}

void SceneLevel1::tick(u16 keys) {

    if(Game < StartGame){

        ballen.push_back(createBall(BALLKLEIN,1,-1,30,60));
        ballen.push_back(createBall(BALLMIDDEL,1,-1,50,90));
        ballen.push_back(createBall(BALLGROOT,1,-1,70,100));
        Game++;
    }
    if(keys & KEY_LEFT) {
        Person->setVelocity(-2, 0);


    } else if(keys & KEY_RIGHT) {
        Person->setVelocity(+2, 0);

    } else {
        Person->setVelocity(0, 0);
    }
    if((keys & KEY_A)) {


        ballen.push_back(createBall(BALLGROOT,1,-1,70,100));
        // b->setDestination(randomDestinations[rand() % 6]);

    }
    if( keys & KEY_UP && bullets.size()< MAXBULLETS) {
        bullets.push_back(createBullet());
    }

    bullet_offScreen();
    bullet_hit_ball();
    ball_hit_person();
    for(auto &b : ballen) {
        b->tick();
    }

}