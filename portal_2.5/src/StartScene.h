//
// Created by Wouter Groeneveld on 02/08/18.
//

#ifndef GBA_SPRITE_ENGINE_SAMPLE_STARTSCENE_H
#define GBA_SPRITE_ENGINE_SAMPLE_STARTSCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class StartScene : public Scene {
private:
    std::unique_ptr<Sprite> chell, portalOut, portal;
    std::unique_ptr<Background> bg;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    StartScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}


    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_SAMPLE_START_SCENE_H