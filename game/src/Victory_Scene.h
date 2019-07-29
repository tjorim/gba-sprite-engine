//
// Created by Florian on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H


#include <libgba-sprite-engine/scene.h>
#include "Adventurer.h"
#include "Chalice.h"

class Victory_Scene : public Scene {
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> adventurer;
    std::unique_ptr<Adventurer> adventurer_object;
    std::unique_ptr<Sprite> chalice;
    std::unique_ptr<Chalice> chalice_object;


public:

    Victory_Scene(std::shared_ptr<GBAEngine> engine) : Scene(engine)  {}


    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;



    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_VICTORY_SCENE_H
