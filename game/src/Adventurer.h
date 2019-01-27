//
// Created by Florian on 5/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ADVENTURER_H
#define GBA_SPRITE_ENGINE_PROJECT_ADVENTURER_H


#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/gba/tonc_math.h>

class Adventurer {
private:
    std::unique_ptr<Sprite> adventurer;
    std::unique_ptr<Sprite> healtbar;
    bool alive = true;
    int lifePoints = 40;
    int stamina = 100;


public:
    Adventurer(std::unique_ptr<Sprite> s1, std::unique_ptr<Sprite> s2): adventurer(std::move(s1)), healtbar(std::move(s2)){}
    Adventurer(std::unique_ptr<Sprite> s1): adventurer(std::move(s1)){}

    Sprite *getAdventurerSprite() {return adventurer.get();}
    Sprite *getHealthbar() {return healtbar.get();}
    int getLifePoints();
    void setLifePoints(int value);
    bool getAlive();
    void setAlive(bool value);
    void attack();
    int getStamina();
    void setStamina(int value);
    void tick(u16 keys);


};


#endif //GBA_SPRITE_ENGINE_PROJECT_ADVENTURER_H
