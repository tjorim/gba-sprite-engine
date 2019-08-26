//
// Created by tiele on 18/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SIMON_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_SIMON_SCENE_H

#include <libgba-sprite-engine/gba_engine.h>
//#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../enums/colour.h"

#include "game_result.h"
#include "../game_scene/player.h"

class SimonScene : public Scene {
private:
    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    std::unique_ptr<Sprite> blue_colour, green_colour, red_colour, yellow_colour;
    std::vector <std::unique_ptr<Sprite>> colours;
    std::unique_ptr<GameResult> game_result;
    std::shared_ptr<Player> player;

    bool a_last = true, b_last = true;
    bool a_now = true, b_now = true;

    bool down_last = false, up_last = false;
    bool down_now = false, up_now = false;

    bool left_last = false, right_last = false;
    bool left_now = false, right_now = false;

    // blue, green, red, yellow
    bool input_colours[4] = {false, false, false, false};
    bool output_colours[4] = {false, false, false, false};

    int n = 16, score = 1;
	int input_seq[16], output_seq[16], dood = 0;

    void createColours();

    void updateColours();

    void resetOutputColours();

    void generateSequence();

    void showSeqColours();

    void getInputSeq();

public:
    SimonScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SIMON_SCENE_H
