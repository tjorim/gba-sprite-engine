//
// Created by Florian on 26/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H


#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class DeathScene : public Scene{
private:

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    DeathScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;


};


#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSCENE_H
