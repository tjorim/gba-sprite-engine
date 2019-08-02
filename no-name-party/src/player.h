//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

enum class Character : char {LUIGI = 0, PRINCESS_PEACH = 1};
// we only have four directions, so no need for ints!
enum class Direction : char {ONDER = 0, LINKS = 1, RECHTS = 2, BOVEN = 3};

class Player {
private:
    std::unique_ptr<Sprite> sprite;
    // De x-positie van the player
    int xCo = GBA_SCREEN_WIDTH / 2 - 16;
    // De y-positie van the player
    int yCo = GBA_SCREEN_HEIGHT / 2 - 16;

    int playerNumber = 0;
    int beginFrame = 0;

    // LUIGI, PRINCESS_PEACH
    Character character = Character::LUIGI;
    // ONDER, LINKS, RECHTS, BOVEN
    Direction direction = Direction::ONDER;

    int score = 3;

public:
    Player();

    Sprite* getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Player::sprite = std::move(sprite);
    }

    void moveTo(int xValue, int yValue);
    void moveRelative(int xValue, int yValue);

    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    void updateBeginFrame();

    /**
     * Wat is de x-positie van this Thing?
     *
     * @return De x-positie van this Thing.
     */
    int getXCo() const;
    /**
     * Stel de x-positie van de speler in.
     *
     * @param xCo De x-positie van de speler.
     */
    void setXCo(int value);

    /**
     * Wat is de y-positie van this Thing?
     *
     * @return De y-positie van this Thing.
     */
    int getYCo() const;
    /**
     * Stel de y-positie van de speler in.
     *
     * @param yCo De y-positie van de speler.
     */
    void setYCo(int value);

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
