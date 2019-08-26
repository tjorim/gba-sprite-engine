//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "car.h"
#include "game_result.h"
#include "../game_scene/player.h"

class RaceScene : public Scene {
private:
    std::unique_ptr <Background> background_tiles;
    std::vector <std::unique_ptr<Sprite>> bombs;
    std::unique_ptr <Car> car;
    std::vector <std::unique_ptr<Sprite>> mushrooms;
    std::unique_ptr<GameResult> game_result;
    std::shared_ptr<Player> player;

    bool a_last = true, b_last = true;
    bool a_now = true, b_now = true;

    int xCo = GBA_SCREEN_WIDTH / 2 - 8, yCo = 0;
    int lives = 3;
    bool playing = false, ended = false;
    bool hit_last = false, hit_now = false;

public:
    RaceScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    void placeBombs();

    void giveLives();

    int getLives();

    void takeLife();

    void startPlaying();

    void stopPlaying();

    void checkCollision();

    void endGame(Result result);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H
