//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "enums/character.h"
#include "enums/result.h"

#include "../sprites/foreground/luigi_game.h"
#include "../sprites/foreground/mario_game.h"
#include "../sprites/foreground/princess_peach_game.h"
#include "../sprites/foreground/yoshi_game.h"

class GameResult {
private:
    std::unique_ptr<Sprite> sprite;

    int beginFrame = 0;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;
    // LOSE, WIN
    Result result = Result::LOSE;

public:
    GameResult(Character character, Result result) : character(character), result(result) {
        SpriteBuilder<Sprite> builder;

        switch (character) {
            case Character::LUIGI:
                setSprite(builder.withData(luigi_gameTiles, sizeof(luigi_gameTiles))
                                  .withSize(SIZE_64_64)
                                  .withAnimated(getBeginFrame(), 1, 0)
                                  .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                  .buildPtr());
                break;

            case Character::MARIO:
                setSprite(builder.withData(mario_gameTiles, sizeof(mario_gameTiles))
                                  .withSize(SIZE_64_64)
                                  .withAnimated(getBeginFrame(), 1, 0)
                                  .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                  .buildPtr());
                break;

            case Character::PRINCESS_PEACH:
                setSprite(builder.withData(princess_peach_gameTiles, sizeof(princess_peach_gameTiles))
                                  .withSize(SIZE_64_64)
                                  .withAnimated(getBeginFrame(), 1, 0)
                                  .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                  .buildPtr());
                break;

            case Character::YOSHI:
                setSprite(builder.withData(yoshi_gameTiles, sizeof(yoshi_gameTiles))
                                  .withSize(SIZE_64_64)
                                  .withAnimated(getBeginFrame(), 1, 0)
                                  .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                  .buildPtr());
                break;

            default:
                break;
        }
    }

    Sprite *getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        GameResult::sprite = std::move(sprite);
    }

    int getBeginFrame() {
        beginFrame = static_cast<int>(result);
        return beginFrame;
    }

    void updateBeginFrame() {
        beginFrame = static_cast<int>(result);
        sprite->setBeginFrame(beginFrame);
    }

    /**
     * Wat is de character van de speler?
     * LUIGI, PRINCESS_PEACH
     *
     * @return De character van de speler.
     */
    Character getCharacter() const {
        return character;
    }

    /**
     * Wat is de richting van de speler?
     * ONDER, BOVEN, LINKS, RECHTS
     *
     * @return De richting van de speler.
     */
    Result getResult() const {
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
    void setResult(const Result &value) {
        switch (value) {
            case Result::LOSE:
                // pas sprite aan
                break;
            case Result::WIN:
                // pas sprite aan
                break;
            default:
                return;
        }
        result = value;

        updateBeginFrame();
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H
