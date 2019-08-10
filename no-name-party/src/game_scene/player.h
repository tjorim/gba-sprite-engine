//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

#include "../enums/character.h"
#include "../enums/direction.h"

class Player {
private:
    std::unique_ptr<Sprite> sprite_down, sprite_left, sprite_right, sprite_up;

    int playerNumber = 0;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;
    // DOWN, LEFT, RIGHT, UP
    Direction direction = Direction::DOWN;

    int score = 3;
    int centerX = GBA_SCREEN_WIDTH / 2 - 16, centerY = GBA_SCREEN_HEIGHT / 2 - 16;

public:
    Player(Character character);

    Sprite *getSprite();

    // getters
    /**
     * Hiermee vraag je het nummer van de speler op.
     *
     * @return het nummer van de speler.
     */
    int getPlayerNumber() const;

    /**
     * Wat is de character van de speler?
     * LUIGI, PRINCESS_PEACH
     *
     * @return De character van de speler.
     */
    Character getCharacter() const;

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
     * Geef de speler een character.
     * LUIGI, PRINCESS_PEACH
     *
     * @param character De character die de speler krijgt.
     */
    void setCharacter(const Character &value);

    /**
     * Geef de speler een richting.
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @param richting De richting die de speler krijgt.
     */
    void setDirection(const Direction &value);

    /**
     * Hiermee verhoog je de score van de speler.
     */
    void scoreHoger();

    /**
     * Hiermee verlaag je de score van de speler.
     */
    void scoreLager();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
