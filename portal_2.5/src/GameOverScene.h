//
// Created by Leander on 24/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H


#include <libgba-sprite-engine/scene.h>

class GameOverScene : public Scene  {
private:
    std::unique_ptr<Sprite> cake;
    std::unique_ptr<Background> bg;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    GameOverScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_GAMEOVERSCENE_H
