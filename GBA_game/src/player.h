//
// Created by joost on 12/12/2018.
//
#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/sprites/affine_sprite.h>

enum Direction {
    DirectionLeft,DirectionRight
};

class Player : public AffineSprite{
private:
    Direction direction = Direction::DirectionRight;
    int amtLives;
    bool runningState;

    bool isBall = false;
    bool canTakeDamage = true;
    int ballSpeed = 1;
public:

    bool getRunnigsState() const {return runningState;}
    void setRunningsState(bool runningState);
    void setDirection(Direction direction);
    Direction getDirection() const { return direction;}
    void setAmtLives(int amtLives);
    int getAmtLives() const { return  amtLives; }

    bool getIsBall() {return isBall;}
    void setIsBall(bool isBall);
    bool getCanTakeDamage() {return canTakeDamage;}
    void setCanTakeDamage(bool canTakeDamage);
    int getBallSpeed() {return ballSpeed;}
    void setBallSpeed(int ballSpeed);

    //Player(int amtLives);
    Player(const void* imgData, int imgSize, int xC, int yC, SpriteSize spriteSize);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

