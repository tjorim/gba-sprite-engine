//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include "../thing.h"

class Player : public Thing {
private:
    int xCoSprite;
    int yCoSprite;
public:
    Player(int xCoGrid, int yCoGrid);
    void move(int xValue, int yValue);

    thingType getType() override;

    /**
     * Wat is de x-positie van this Thing?
     *
     * @return De x-positie van this Thing.
     */
    int getXCoSprite() const;
    /**
     * Stel de x-positie van de speler in.
     *
     * @param xCoGrid De x-positie van de speler.
     */
    void setXCoSprite(int value);

    /**
     * Wat is de y-positie van this Thing?
     *
     * @return De y-positie van this Thing.
     */
    int getYCoSprite() const;
    /**
     * Stel de y-positie van de speler in.
     *
     * @param yCoGrid De y-positie van de speler.
     */
    void setYCoSprite(int value);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
