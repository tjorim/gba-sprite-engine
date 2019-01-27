//
// Created by Vandebosch Remy on 19/12/2018.
//

#include "Luigi.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::unique_ptr<AffineSprite>& Luigi::getLuigiSprite() {
    return luigiSprite;
}

void Luigi::kill() {
    dead = true;
}

bool Luigi::isDead() {
    return dead;
}

void Luigi::setCurrentLvl(int lvl) {
    CurrentLvl = lvl;
}

int Luigi::getCurrentLvl() {
        return CurrentLvl;
}


void Luigi::tick(u16 keys) {
    if(!isDead()){
      if(luigiSprite->getVelocity().y != 0){
           luigiSprite->stopAnimating();
           luigiSprite->animateToFrame(5);
        }

        if(keys & KEY_RIGHT) {
            if (luigiSprite->getVelocity().y == 0) luigiSprite->animate();
            if(getCurrentLvl() == 2)luigiSprite->setVelocity(1,0);
        }
            else if (luigiSprite->getVelocity().y == 0) {
                luigiSprite->stopAnimating();
                luigiSprite->animateToFrame(0);
            }


        if(keys & KEY_UP){
            if(luigiSprite->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) luigiSprite->setVelocity(0,-1);
        }
        else{

            if(luigiSprite->getY() == GBA_SCREEN_HEIGHT-bottomHeightFor32) {
                if(getCurrentLvl() != 2)luigiSprite->setVelocity(0, 0);
                if(!(keys & KEY_RIGHT)) luigiSprite->animateToFrame(0);
            }
        }

        if((luigiSprite->getY() == GBA_SCREEN_HEIGHT-120 && luigiSprite->getVelocity().y < 0)
           || (luigiSprite->getY() < GBA_SCREEN_HEIGHT-bottomHeightFor32 && luigiSprite->getVelocity().y == 0)) luigiSprite->setVelocity(0,1);
    }
}

void Luigi::tickEndScene(u16 keys) {
    if(!isDead()){
        luigiSprite->setVelocity(0,0);
        if(luigiSprite->getVelocity().y != 0){
            luigiSprite->stopAnimating();
            luigiSprite->animateToFrame(5);
        }
        if(keys & KEY_RIGHT) {
           // luigiSprite->flipHorizontally(false);
            luigiSprite->setVelocity(1, 0);
            if (luigiSprite->getVelocity().y == 0) {
                luigiSprite->animate();
            }
        }
        else if (luigiSprite->getVelocity().y == 0) {
            luigiSprite->stopAnimating();
            luigiSprite->animateToFrame(0);
        }

        if(keys & KEY_LEFT){
            //luigiSprite->flipHorizontally(true);
            luigiSprite->setVelocity(-1,0);
        }


    }

}