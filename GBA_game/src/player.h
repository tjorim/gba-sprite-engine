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
    int aantalLevens;
    bool runningState;
public:

    bool getRunnigsState() const {return runningState;}
    void setRunningsState(bool runningState);
    void setDirection(Direction direction);
    Direction getDirection() const { return direction;}
    void setAantalLevens(int aantalLevens);
    int getAantalLevens() const { return  aantalLevens; }
    //Player(int aantalLevens);
    Player(const void* imgData, int imgSize, int xC, int yC, SpriteSize spriteSize);


};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

