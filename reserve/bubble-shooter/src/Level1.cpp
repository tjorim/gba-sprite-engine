//
// Created by 11401165 on 21/12/2018.
//

#include "Level1.h"

#include "Level2.h"




void Level1::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(background_tiles_spongebobPal, sizeof(background_tiles_spongebobPal)));

    load_always();

    bg = std::unique_ptr<Background>(new Background(1, background_tiles_spongebobTiles, sizeof(background_tiles_spongebobTiles), map_spongebob, sizeof(map_spongebob)));
    bg.get()->useMapScreenBlock(16);

}

void Level1::tick(u16 keys) {


    tick_always(keys);
    if(keys & KEY_LEFT) {
        Person->setVelocity(-2, 0);


    } else if(keys & KEY_RIGHT) {
        Person->setVelocity(+2, 0);

    } else {
        Person->setVelocity(0, 0);
    }
    if(Game < StartGame){

        ballen.push_back(createBall(BALLKLEIN,1,-1,30,60));
        //ballen.push_back(createBall(BALLMIDDEL,1,-1,50,90));
        ballen.push_back(createBall(BALLGROOT,1,-1,70,100));
        TextStream::instance().setText(std::string("Score: ")+ std::to_string(score), 1, 4);
        TextStream::instance().setText(std::string("Aantal ballen: ")+ std::to_string(ballen.size()), 6, 0);
        TextStream::instance().setText(std::string("Aantal bullets: ")+ std::to_string(bullets.size()), 7, 0);
        TextStream::instance().setText(std::string("Bullet cooldown: ")+ std::to_string(bulletCooldown), 3, 6);
        Game++;
    }


    if(ballen.empty()) {
        if(!engine->isTransitioning()) {
            bullets.clear();
            TextStream::instance() << "entered: starting next scene";
            engine->transitionIntoScene(new Level2(engine,score), new FadeOutScene(2));
        }
    }
}