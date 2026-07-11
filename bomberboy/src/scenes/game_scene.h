//
// Created by JT
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../thing.h"
#include "../thing/bomb.h"
#include "../thing/player.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

class GameScene : public Scene {
private:
    int level = 1;
    Thing *board[BOARD_HEIGHT][BOARD_WIDTH];
    std::vector <std::unique_ptr<Bomb>> bombs;
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;

    void updateBombs();
    void explodeBomb(Bomb *bomb);
    bool applyExplosionToTile(int xValue, int yValue);
    bool isInsideBoard(int xValue, int yValue);
    bool isWalkable(int xValue, int yValue);
    void movePlayer(int xValue, int yValue);

public:
    GameScene(const std::shared_ptr <GBAEngine> &engine, int level);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    thingType getThingType(int xValue, int yValue);
    void dropBomb();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H