//
// Created by Florian on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_VICTORY_H
#define GBA_SPRITE_ENGINE_PROJECT_VICTORY_H


#include <libgba-sprite-engine/scene.h>

class Victory : public Scene{
private:




public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    Victory(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;


};


#endif //GBA_SPRITE_ENGINE_PROJECT_VICTORY_H
