//
// Created by Tom Fierens on 7/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H
#define GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H



#include <libgba-sprite-engine/scene.h>

class SplashScreen : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<Sprite> kirby;
    std::unique_ptr<Sprite> kirby_title;
    std::unique_ptr<Sprite> press_start;
    std::unique_ptr<Sprite> space_title;

public:
    SplashScreen(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SPLASHSCREEN_H