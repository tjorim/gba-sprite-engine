//
// Created by Brecht on 22/01/2019.
//

#include <math.h>
#include "level.h"

#define PI 3.14159265

Level::Level(Ground ground, SpaceShip spaceShip, int landingBegin, int landingEnd) {
    this->ground = ground;
    this->spaceShip = spaceShip;
    this->landingBegin = landingBegin;
    this->landingEnd = landingEnd;
    landed = false;
    alive = true;
}

Level::Level(const Level& level) {
    ground = level.ground;
    spaceShip = level.spaceShip;
}

Level::Level() {

}

void Level::step() {
    spaceShip.step();
    float x = spaceShip.getX();
    float y = spaceShip.getY();
    float rotation = spaceShip.getRotation();

    float rotationRad = rotation * PI / 180;

    float coordinates [4][2];
    coordinates[0][0] = x - cos(rotationRad) * 16 + sin(rotationRad) * 16;//x-coordinaat links boven
    coordinates[0][1] = y - sin(rotationRad) * 16 - cos(rotationRad) * 16;//y-coordinaat links boven
    coordinates[1][0] = x + cos(rotationRad) * 16 + sin(rotationRad) * 16;//x-coordinaat rechts boven
    coordinates[1][1] = y + sin(rotationRad) * 16 - cos(rotationRad) * 16;//y-coordinaat rechts boven
    coordinates[2][0] = x + cos(rotationRad) * 16 - sin(rotationRad) * 16;//x-coordinaat rechts onder
    coordinates[2][1] = y + sin(rotationRad) * 16 + cos(rotationRad) * 16;//y-coordinaat rechts onder
    coordinates[3][0] = x - cos(rotationRad) * 16 - sin(rotationRad) * 16;//x-coordinaat links onder
    coordinates[3][1] = y - sin(rotationRad) * 16 + cos(rotationRad) * 16;//y-coordinaat links onder

    for(int i = 0; i < 4; i++){
        std::pair<int, int> leftCoordinate, rightCoordinate;
        std::pair<int, int> coordinate = std::make_pair(coordinates[i][0], coordinates[i][1]);
        ground.getClosestCoordinates(coordinate, leftCoordinate, rightCoordinate);

        //Y = (Y2 - Y1) / (X2 - X1) * (X - X1) + Y1
        if(coordinate.second >= (leftCoordinate.second - rightCoordinate.second) / (leftCoordinate.first - rightCoordinate.first) * (coordinate.first - leftCoordinate.first) + leftCoordinate.second - 13){
            if(spaceShip.canLand() && x - 16 >= landingBegin && x + 16 <= landingEnd) {
                landed = true;
            }
            else {
                alive = false;
            }
        }
    }
}

bool Level::isLanded() {
    return landed;
}

bool Level::isAlive() {
    return alive;
}

void Level::setUp(bool up) {
    spaceShip.up = up;
}

void Level::setLeft(bool left) {
    spaceShip.left = left;
}

void Level::setRight(bool right) {
    spaceShip.right = right;
}

bool Level::getUp() {
    return spaceShip.up;
}

float Level::getX() {
    return spaceShip.getX();
}

float Level::getY() {
    return spaceShip.getY();
}

float Level::getRotation() {
    return spaceShip.getRotation();
}

void Level::restart() {
    spaceShip.restart();
    landed = false;
    alive = true;
}