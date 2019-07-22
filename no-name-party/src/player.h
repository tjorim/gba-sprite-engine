//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include "../thing.h"

// we only have four directions, so no need for ints!
enum class Direction : char {ONDER = 1, BOVEN = 2, LINKS = 3, RECHTS = 4};

class Player : public Thing {
private:
    int xCoSprite;
    int yCoSprite;

    int playerNumber;

    // ONDER, BOVEN, LINKS, RECHTS
    Direction direction = Direction::ONDER;

    int score = 3;

public:
    Player(int xCoGrid, int yCoGrid);
    // override the moveTo as well
    void moveTo(int xValue, int yValue);
    void moveRelative(int xValue, int yValue);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

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

    // getters
    /**
     * Hiermee vraag je het nummer van de speler op.
     *
     * @return het nummer van de speler.
     */
    int getPlayerNumber() const;
    /**
     * Wat is de richting van de speler?
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @return De richting van de speler.
     */
    Direction getDirection() const;
    /**
     * Welke score heeft de speler?
     *
     * @return de score van de speler.
     */
    int getScore() const;

    // setters
    /**
     * Hiermee stel je het nummer van de speler in.
     *
     * @param spelerNr Het nummer van de speler.
     */
    void setPlayerNumber(int value);
    /**
     * Geef de speler een richting.
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @param richting De richting die de speler krijgt.
     */
    void setDirection(const Direction &value);

    /**
     * Hiermee neem je een bom af van de speler.
     */
    void eenBomMinder();
    /**
     * Hiermee geef je de speler een bom meer.
     */
    void eenBomMeer();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
