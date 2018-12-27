//
// Created by Tom Fierens on 10/12/18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H


#include <libgba-sprite-engine/scene.h>

class start_screen : public Scene {
private:
    std::unique_ptr<Background> bg;

public:
    start_screen(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};


#endif //GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H
