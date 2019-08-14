//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../enums/character.h"
#include "../enums/result.h"

#include "foreground/sprites/luigi_game_lose.h"
#include "foreground/sprites/luigi_game_win.h"

#include "foreground/sprites/mario_game_lose.h"
#include "foreground/sprites/mario_game_win.h"

#include "foreground/sprites/princess_peach_game_lose.h"
#include "foreground/sprites/princess_peach_game_win.h"

#include "foreground/sprites/yoshi_game_lose.h"
#include "foreground/sprites/yoshi_game_win.h"

class GameResult {
private:
    std::unique_ptr<Sprite> sprite_lose, sprite_win;

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
                sprite_lose = std::move(builder.withData(luigi_game_loseTiles,
                                                         sizeof(luigi_game_loseTiles))
                                                .withSize(SIZE_64_64)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                                .buildPtr());

                sprite_win = std::move(builder.withData(luigi_game_winTiles,
                                                        sizeof(luigi_game_winTiles))
                                               .withSize(SIZE_64_64)
                                               .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                               .buildPtr());
                break;

            case Character::MARIO:
                sprite_lose = std::move(builder.withData(mario_game_loseTiles,
                                                         sizeof(mario_game_loseTiles))
                                                .withSize(SIZE_64_64)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                                .buildPtr());

                sprite_win = std::move(builder.withData(mario_game_winTiles,
                                                        sizeof(mario_game_winTiles))
                                               .withSize(SIZE_64_64)
                                               .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                               .buildPtr());
                break;

            case Character::PRINCESS_PEACH:
                sprite_lose = std::move(builder.withData(princess_peach_game_loseTiles,
                                                         sizeof(princess_peach_game_loseTiles))
                                                .withSize(SIZE_64_64)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                                .buildPtr());

                sprite_win = std::move(builder.withData(princess_peach_game_winTiles,
                                                        sizeof(princess_peach_game_winTiles))
                                               .withSize(SIZE_64_64)
                                               .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                               .buildPtr());
                break;

            case Character::YOSHI:
                sprite_lose = std::move(builder.withData(yoshi_game_loseTiles,
                                                         sizeof(yoshi_game_loseTiles))
                                                .withSize(SIZE_64_64)
                                                .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                                .buildPtr());

                sprite_win = std::move(builder.withData(yoshi_game_winTiles,
                                                        sizeof(yoshi_game_winTiles))
                                               .withSize(SIZE_64_64)
                                               .withLocation(GBA_SCREEN_WIDTH / 2 - 32, GBA_SCREEN_HEIGHT / 2 - 64)
                                               .buildPtr());
                break;

            default:
                break;
        }
    }

    Sprite *getSprite() {
        switch (result) {
            case Result::LOSE:
                return sprite_lose.get();
                break;

            case Result::WIN:
                return sprite_win.get();
                break;

            default:
                break;
        }
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

        //updateBeginFrame();
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

        //updateBeginFrame();
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_RESULT_H
