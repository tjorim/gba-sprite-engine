//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "stair_case.h"

class BookScene : public Scene {
private:
    std::unique_ptr<Background> background_books;
    std::vector<std::unique_ptr<Sprite>> books;

public:
    BookScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOOK_SCENE_H
