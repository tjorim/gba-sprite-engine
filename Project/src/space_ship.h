//
// Created by Brecht on 22/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SPACE_SHIP_H
#define GBA_SPRITE_ENGINE_PROJECT_SPACE_SHIP_H


class SpaceShip {
private:
    float x, y, vx, vy, rotation;
    float gravity, motorForce, rotationSpeed;
    float startX, startY;
public:
    bool left, right, up;

    SpaceShip() : x(160), startX(160), y(100), startY(100), vx(0), vy(0), rotation(360), gravity(1), motorForce(1.5), rotationSpeed(1), left(false), right(false), up(false) {};
    SpaceShip(float x0, float y0, float gravity0, float motorForce0, float rotationSpeed0) : x(x0), startX(x0), y(y0), startY(y0), vx(0), vy(0), rotation(360), gravity(gravity0), motorForce(motorForce0), rotationSpeed(rotationSpeed0), left(false), right(false), up(false) {};

    void step();
    float getX();
    float getY();
    float getRotation();

    bool canLand();

    void restart();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SPACE_SHIP_H
