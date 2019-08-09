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
    int character = 0;
    //Thing *board[BOARD_HEIGHT][BOARD_WIDTH];
    //std::array<std::array<Thing, BOARD_WIDTH>, BOARD_HEIGHT> board;
    //std::vector <std::unique_ptr<Bomb>> bombs;
    std::unique_ptr<Player> player;
    std::unique_ptr<GameResult> result;

public:
    GameScene(const std::shared_ptr<GBAEngine> &engine, int character);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    int getCharacter() const;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GAME_SCENE_H