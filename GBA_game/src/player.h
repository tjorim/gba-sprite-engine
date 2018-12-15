//
// Created by joost on 12/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

enum Direction {
    DirectionLeft,DirectionRight
};



class Player {
private:

    Direction direction = Direction::DirectionRight;
    int aantalLevens;
public:

    void setDirection(Direction direction);
    void setAantalLevens(int aantalLevens);
    int getAantalLevens() const { return  aantalLevens; }
    Player(int aantalLevens);


};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

