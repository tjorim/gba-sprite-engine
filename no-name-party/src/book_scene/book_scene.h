//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "book.h"
#include "stair_case.h"
#include "game_result.h"
#include "../game_scene/player.h"

class BookScene : public Scene {
private:
    std::unique_ptr <Background> background_books;
    std::vector <std::unique_ptr<Book>> books;
    std::unique_ptr <StairCase> stair_case;
    std::unique_ptr<GameResult> game_result;
    std::shared_ptr<Player> player;

    bool a_last = true, b_last = true;
    bool a_now = true, b_now = true;

    bool down_last = false, up_last = false;
    bool down_now = false, up_now = false;

    bool left_last = false, right_last = false;
    bool left_now = false, right_now = false;

    int height = 0;
    int xCo = GBA_SCREEN_WIDTH / 2 - 8;

public:
    BookScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    void placeBooks();

    void higher();

    void lower();

    void updateHeight();

    void goLeft();

    void goRight();

    void updateXCo();
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H
