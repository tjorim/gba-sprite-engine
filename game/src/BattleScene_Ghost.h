//
// Created by Florian on 26/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BATTLESCENE_SKELETON_H
#define GBA_SPRITE_ENGINE_PROJECT_BATTLESCENE_SKELETON_H


#include <libgba-sprite-engine/gba_engine.h>
#include "Adventurer.h"
#include "Ghost.h"

class BattleScene_Ghost : public Scene {
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> adventurer;
    std::unique_ptr<Adventurer> adventurer_object;
    std::unique_ptr<Sprite> ghost;
    std::unique_ptr<Ghost> ghost_object;
    std::unique_ptr<Sprite> healthbar;

    int scrollX, scrollY;

public:

    BattleScene_Ghost(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;



    void load() override;
    void tick(u16 keys) override;


};


#endif //GBA_SPRITE_ENGINE_PROJECT_BATTLESCENE_SKELETON_H
