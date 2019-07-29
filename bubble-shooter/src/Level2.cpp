//
// Created by 11401165 on 21/12/2018.
//

#include "Level2.h"
#include "Level1.h"

#define WALL_X  100

//

void Level2::atStartGame() {
    createWall();
    ballen.push_back(createBall(BALLMIDDEL,1,-1,130,60));
    ballen.push_back(createBall(BALLGROOT,1,-1,150,90));
    ballen.push_back(createBall(BALLMIDDEL,-1,-1,10,10));

}


std::vector<Sprite *> Level2::sprites() {
    std::vector<Sprite*> sprites;

    for(auto& b : ballen) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : bullets) {
        sprites.push_back(b.get());
    }
    for(auto& w : wall) {
        sprites.push_back(w.get());
    }

    sprites.push_back(Brick.get());
    sprites.push_back(ballSmall.get());
    sprites.push_back(ballBig.get());
    sprites.push_back(ballMedium.get());
    sprites.push_back(bullet.get());
    sprites.push_back(person.get());
    return sprites;

}

void Level2::ball_collides_wall(){

    for(auto &b : ballen){
        for(auto &w : wall){
            if( b->getSprite()->collidesWith(*w.get())){
                auto vel = b->getSprite()->getVelocity();
                auto pos = b->getSprite()->getPos();
                b->setDx(-vel.x);
                b->getSprite()->moveTo(pos.x + 2*(-vel.x) ,pos.y);
                return;
            }
        }
    }


}

void Level2::check_open_wall(){
       if( ballen.size() <= 2){
        wall.clear();
    }
}

int Level2::person_side_of_wall(){

    if((person->getX()+ person->getWidth()) <= (WALL_X + Brick->getWidth()/2) ){
        return RIGHT;
    }
    else{
        return LEFT;
    }

}

bool Level2::check_allowed_move_person(int direction){

    if( person_collides_wall() == false || wall.empty()){
        return true;
    }
    else{
        if( person_side_of_wall() == RIGHT && direction == LEFT){
            return true;
        }
        else if( person_side_of_wall() == LEFT && direction == RIGHT){
            return true;
        }
    }

return false;

}

bool Level2::person_collides_wall(){

    for(auto &w : wall){
        if( person.get()->collidesWith(*w.get())){
            return true;
        }
    }
return false;
}

void Level2::createWall(){

    for (int i = 0; i < 5; i++){
        wall.push_back(spriteBuilder->withLocation(WALL_X,i*Brick->getHeight()).buildWithDataOf(*Brick.get()));
    }

}

void Level2::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(wall_windowPal, sizeof(wall_windowPal)));
    loadAlways();

    Brick = spriteBuilder
            ->withData(wallTiles, sizeof(wallTiles))
            .withSize(SIZE_16_32)
            .withLocation(-40, -40)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, wall_window_tiles, sizeof(wall_window_tiles), wall_map, sizeof(wall_map)));
    bg.get()->useMapScreenBlock(16);
}



void Level2:: movePerson(u16 keys) {

    int velx = 2;

    if(keys & KEY_RIGHT && check_allowed_move_person(LEFT)) {
        person->setVelocity(-velx, 0);
        scrollX--;
        bg.get()->scroll(scrollX,0);
    } else if(keys & KEY_LEFT && check_allowed_move_person(RIGHT)) {
        person->setVelocity(+velx, 0);
        scrollX++;
        bg.get()->scroll(scrollX,0);
    } else {
        person->setVelocity(0, 0);
    }

}

void Level2::tick(u16 keys) {

    tickAlways(keys);

    ball_collides_wall();
    check_open_wall();


    if(ballen.empty()) {

        if(!engine->isTransitioning()) {
            bullets.clear();
            TextStream::instance() << "entered: starting next scene";
            engine->transitionIntoScene(new Level1(engine,score), new FadeOutScene(2));

        }
    }


}