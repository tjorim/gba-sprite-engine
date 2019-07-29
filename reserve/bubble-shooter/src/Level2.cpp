//
// Created by 11401165 on 21/12/2018.
//

#include "Level2.h"
#include "Level1.h"

#define WALL_X  100



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
    sprites.push_back(BallSmall.get());
    sprites.push_back(BallBig.get());
    sprites.push_back(BallMedium.get());
    sprites.push_back(Bullet.get());
    sprites.push_back(Person.get());
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
    TextStream::instance().setText(std::string("SCORE 2: ")+ std::to_string(score), 10, 2);
    if( ballen.size() <= 2){
        wall.clear();
    }
}

int Level2::person_side_of_wall(){

    if((Person->getX()+ Person->getWidth()) <= (WALL_X + Brick->getWidth()/2) ){
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
        if( Person.get()->collidesWith(*w.get())){
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
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));
    load_always();

    Brick = spriteBuilder
            ->withData(wallTiles, sizeof(wallTiles))
            .withSize(SIZE_16_32)
            .withLocation(-40, -40)
            .buildPtr();

    //bg = std::unique_ptr<Background>(new Background(1, background_tiles_spongebobTiles, sizeof(background_tiles_spongebobTiles), map_spongebob, sizeof(map_spongebob)));
    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);


}



void Level2::tick(u16 keys) {

    tick_always(keys);

    if(keys & KEY_LEFT && check_allowed_move_person(LEFT)) {
        Person->setVelocity(-2, 0);
    } else if(keys & KEY_RIGHT && check_allowed_move_person(RIGHT)) {
        Person->setVelocity(+2, 0);
    } else {
        Person->setVelocity(0, 0);
    }

    if(Game < StartGame){
        createWall();
        ballen.push_back(createBall(BALLMIDDEL,1,-1,130,60));
        ballen.push_back(createBall(BALLGROOT,1,-1,150,90));
        ballen.push_back(createBall(BALLMIDDEL,-1,-1,10,10));
        TextStream::instance().setText(std::string("Score: ")+ std::to_string(score), 1, 4);
        TextStream::instance().setText(std::string("Aantal ballen: ")+ std::to_string(ballen.size()), 6, 0);
        TextStream::instance().setText(std::string("Aantal bullets: ")+ std::to_string(bullets.size()), 7, 0);
        TextStream::instance().setText(std::string("Bullet cooldown: ")+ std::to_string(bulletCooldown), 3, 6);
        Game++;
    }
    TextStream::instance().setText(std::string("SIZE OF WALL: ")+ std::to_string(wall.size()), 8, 6);
    ball_collides_wall();
    check_open_wall();

    if(ballen.empty()) {
        TextStream::instance() << "entered: starting next scene";
        if(!engine->isTransitioning()) {
            bullets.clear();

            //engine->transitionIntoScene(new Level1(engine,score), new FadeOutScene(2));
            engine->transitionIntoScene(new Level1(engine), new FadeOutScene(2));
        }
    }


}