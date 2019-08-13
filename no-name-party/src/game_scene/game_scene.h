//
// Created by JT
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "game_result.h"

class GameScene : public Scene {
private:
    std::unique_ptr<Background> background_map;
    //Thing *board[BOARD_HEIGHT][BOARD_WIDTH];
    //std::array<std::array<Thing, BOARD_WIDTH>, BOARD_HEIGHT> board;
    //std::vector <std::unique_ptr<Bomb>> bombs;
    std::unique_ptr<Player> player;
    std::unique_ptr<GameResult> result;

    int character = 0;

    // De x-positie van the player
    int xCo = GBA_SCREEN_WIDTH / 2 - 16;
    // De y-positie van the player
    int yCo = GBA_SCREEN_HEIGHT / 2 - 16;

public:
    GameScene(const std::shared_ptr<GBAEngine> &engine, int character);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    int getCharacter() const;

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
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H