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

    // kan de speler shiften?
    bool shift = false;
    // kan de speler kicken?
    bool kick = false;
    // ONDER, BOVEN, LINKS, RECHTS
    Direction direction = Direction::ONDER;

    int aantalBommen = 1;
    int standaardBommen = 1;
    int maxBommen = 6;
    int hoeveelVuur = 1;
    int standaardVuur = 1;
    int maxVuur = 6;
    int lives = 3;
    int standaardLevens = 3;
    int maxLevens = 3;
    int speed = 1;
    int standaardSnelheid = 1;
    int maxSnelheid = 6;

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
     * Kan de speler bommen shiften?
     *
     * @return True als de speler bommen kan shiften.
     */
    bool canShift() const;
    /**
     * Kan de speler bommen kicken?
     *
     * @return True als de speler bommen kan kicken.
     */
    bool canKick() const;
    /**
     * Wat is de richting van de speler?
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @return De richting van de speler.
     */
    Direction getDirection() const;
    /**
     * Hoeveel bommen heeft de speler nog?
     *
     * @return het aantal bommen van de speler.
     */
    int getAantalBommen() const;
    /**
     * Hoeveel bommen kan de speler maximum hebben?
     *
     * @return het maximum aantal bommen van de speler.
     */
    int getMaxBommen();
    /**
     * Hoe krachtig is de explosie van de speler?
     *
     * @return De 'krachtigheid' van de explosie van de speler.
     */
    int getHoeveelVuur() const;
    /**
     * Hoe krachtig kan de explosie van de speler maximum zijn?
     *
     * @return De maximale 'krachtigheid' van de explosie van de speler.
     */
    int getMaxVuur() const;
    bool isDood();
    /**
     * Hoeveel levens heeft de speler nog?
     *
     * @return het aantal levens van de speler.
     */
    int getLives() const;
    /**
     * Hoeveel levens kan de speler maximum hebben?
     *
     * @return het maximum aantal levens van de speler.
     */
    int getMaxLevens();
    /**
     * Welke snelheid heeft de speler?
     *
     * @return snelheid De snelheid van de speler.
     */
    int getSpeed() const;
    /**
     * Welke snelheid kan de speler maximaal hebben?
     *
     * @return maxSnelheid De maximale snelheid van de speler.
     */
    int getMaxSnelheid();

    // setters
    /**
     * Hiermee stel je het nummer van de speler in.
     *
     * @param spelerNr Het nummer van de speler.
     */
    void setPlayerNumber(int value);
    /**
     * Laat de speler bommen shiften.
     *
     * @param shiften True als de speler bommen mag shiften.
     */
    void setShift(bool value);
    /**
     * Laat de speler bommen kicken.
     *
     * @param kicken True als de speler bommen mag kicken.
     */
    void setKick(bool value);
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
    /**
     * Geef de speler max bommen.
     */
    void geefMaxBommen();
    /**
     * Hiermee pas je de kracht van de explosie van de speler aan.
     *
     * @param hoeveelVuur De 'krachtigheid' van de explosie van de speler.
     */
    void setHoeveelVuur(int value);
    /**
     * Hiermee vermoord je de speler, het aantal levens wordt op nul gezet.
     */
    void maakDood();
    /**
     * Hiermee neem je een leven af van de speler.
     */
    void eenLevenMinder();
    /**
     * Hiermee geef je de speler een leven meer.
     */
    void eenLevenMeer();
    /**
     * Geef de speler max levens.
     */
    void geefMaxLevens();
    /**
     * Hiermee pas je de snelheid van de speler aan.
     *
     * @param snelheid De snelheid van de speler.
     */
    void setSpeed(int value);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
