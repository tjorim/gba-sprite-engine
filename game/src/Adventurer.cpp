//
// Created by Florian on 5/01/2019.
//

#include <libgba-sprite-engine/gba_engine.h>
#include "Adventurer.h"


int Adventurer::getLifePoints() {
    return lifePoints;
}
void Adventurer::setLifePoints(int value) {
    lifePoints = value;
}
bool Adventurer::getAlive() {
    if(lifePoints>0){
        return true;
        }
    else{
        return false;}
}
void Adventurer::setAlive(bool value) {
    alive = value;
}
int Adventurer::getStamina() {
    return stamina;
}
void Adventurer::setStamina(int value) {
    stamina = value;
}

void Adventurer::tick(u16 keys) {

    if(keys & KEY_LEFT) {
        getAdventurerSprite()->makeAnimated(5,10);
        getAdventurerSprite()->setVelocity(-1,0);
        getAdventurerSprite()->flipHorizontally(true);
    } else if(keys & KEY_RIGHT) {
        getAdventurerSprite()->makeAnimated(5,10);
        getAdventurerSprite()->setVelocity(+1, 0);
        getAdventurerSprite()->flipHorizontally(false);
    } else if(keys & KEY_A ) {
        getAdventurerSprite()->animateToFrame(7);
        getAdventurerSprite()->setVelocity(0, 0);
    } else {
        getAdventurerSprite()->animateToFrame(6);
        getAdventurerSprite()->stopAnimating();
        getAdventurerSprite()->setVelocity(0, 0);
    }
    if(lifePoints == 40){
        getHealthbar()->animateToFrame(0);
        getHealthbar()->stopAnimating();
    } else if (lifePoints == 30){
        getHealthbar()->animateToFrame(1);
        getHealthbar()->stopAnimating();
    } else if (lifePoints == 20){
        getHealthbar()->animateToFrame(2);
        getHealthbar()->stopAnimating();
    } else if (lifePoints == 10){
        getHealthbar()->animateToFrame(3);
        getHealthbar()->stopAnimating();
    } else if (lifePoints == 0){
        getHealthbar()->animateToFrame(4);
        getHealthbar()->stopAnimating();
        setAlive(false);
    }


};


