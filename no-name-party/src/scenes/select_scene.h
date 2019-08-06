//
// Created by Jorim Tielemans
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

class SelectScene : public Scene {
private:
    std::unique_ptr<Background> bg_map;
    std::unique_ptr<SpriteBuilder<Sprite>> spriteBuilder;
    //std::unique_ptr<Sprite> luigi_select, princess_peach_select, mario_select, yoshi_select;
    std::vector<std::unique_ptr<Sprite>> characters;

    bool left_last = false, right_last = false;
    bool left_now = false, right_now = false;

    int character_previous = 0, character_current = 0;

    void characterLeft();

    void characterRight();

public:
    SelectScene(const std::shared_ptr<GBAEngine> &engine);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    int getCharacter() const;

    void setCharacter(int character);

    void updateCharacter();

    void unselectCharacter(int character);

    void selectCharacter(int character);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_SELECT_SCENE_H