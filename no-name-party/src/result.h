//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_RESULT_H
#define GBA_SPRITE_ENGINE_PROJECT_RESULT_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "character.h"
#include "../sprites/game_result.h"

enum class Game : char {LOSE = 0, WIN = 1};

class Result {
private:
    std::unique_ptr<Sprite> sprite;

    int beginFrame = 0;

    // LUIGI, PRINCESS_PEACH, MARIO, YOSHI
    Character character = Character::LUIGI;
    // ONDER, LINKS, RECHTS, BOVEN
    Game result = Game::LOSE;

public:
    Result(Character character, Game result) : character(character), result(result) {
        SpriteBuilder<Sprite> spriteBuilder;
        setSprite(spriteBuilder
                .withData(game_resultTiles, sizeof(game_resultTiles))
                .withSize(SIZE_64_64)
                .withAnimated(getBeginFrame(), 1, 0)
                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                .buildPtr());
    }

    Sprite* getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Result::sprite = std::move(sprite);
    }

    int getBeginFrame() {
        beginFrame = 2 * static_cast<int>(character) + static_cast<int>(result);
        return beginFrame;
    }

    void updateBeginFrame() {
        beginFrame = 2 * static_cast<int>(character) + static_cast<int>(result);
        sprite->setBeginFrame(beginFrame);
    }

    /**
     * Wat is de character van de speler?
     * LUIGI, PRINCESS_PEACH
     *
     * @return De character van de speler.
     */
    Character getCharacter() const
    {
        return character;
    }
    /**
     * Wat is de richting van de speler?
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @return De richting van de speler.
     */
    Game getResult() const
    {
        return result;
    }

    /**
     * Geef de speler een character.
     * LUIGI, PRINCESS_PEACH
     *
     * @param character De character die de speler krijgt.
     */
    void setCharacter(const Character &value) {
        switch (value) {
        case Character::LUIGI:
            // pas sprite aan
            break;
        case Character::PRINCESS_PEACH:
            // pas sprite aan
            break;
        default:
            return;
        }
        character = value;

        updateBeginFrame();
    }
    /**
     * Geef de speler een richting.
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @param richting De richting die de speler krijgt.
     */
    void setResult(const Game &value) {
        switch (value) {
        case Game::LOSE:
            // pas sprite aan
            break;
        case Game::WIN:
            // pas sprite aan
            break;
        default:
            return;
        }
        result = value;

        updateBeginFrame();
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_RESULT_H
