//
// Created by Brecht on 22/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H

#include "space_ship.h"
#include "ground.h"

class Level {
private:
    Ground ground;
    bool landed, alive;
    SpaceShip spaceShip;
public:
    int landingBegin, landingEnd;

    Level();
    Level(Ground ground, SpaceShip spaceShip, int landingBegin, int landingEnd);
    Level(const Level& level);

    void step();
    bool isLanded();
    bool isAlive();

    void setUp(bool up);
    void setLeft(bool left);
    void setRight(bool right);
    bool getUp();

    float getX();
    float getY();
    float getRotation();

    void restart();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
