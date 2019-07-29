//
// Created by Florian on 3/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STARTSPELSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_STARTSPELSCENE_H

#include "Adventurer.h"
#include "EyeballMonster.h"


#include <libgba-sprite-engine/gba_engine.h>



class BattleScene_EyeMonster : public Scene{
private:
    std::unique_ptr<Background> background;
    std::unique_ptr<Sprite> adventurer;
    std::unique_ptr<Adventurer> adventurer_object;
    std::unique_ptr<Sprite> eyeball;
    std::unique_ptr<EyeballMonster> eyeball_object;
    std::unique_ptr<Sprite> healthbar;

    int scrollX, scrollY;


public:

    BattleScene_EyeMonster(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;



    void load() override;
    void tick(u16 keys) override;
};





#endif //GBA_SPRITE_ENGINE_PROJECT_STARTSPELSCENE_H
