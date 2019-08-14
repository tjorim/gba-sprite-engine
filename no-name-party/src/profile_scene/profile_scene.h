//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "../enums/character.h"

class ProfileScene : public Scene {
private:
    std::unique_ptr<Background> background_profile;

    bool a_last = true, b_last = true;
    bool a_now = true, b_now = true;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;

public:
    ProfileScene(const std::shared_ptr<GBAEngine> &engine, Character character);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    /**
     * Wat is de character van de speler?
     * LUIGI, MARIO, PRINCESS_PEACH, YOSHI
     *
     * @return De character van de speler.
     */
    Character getCharacter() const;

    /**
     * Geef de speler een character.
     * LUIGI, MARIO, PRINCESS_PEACH, YOSHI
     *
     * @param character De character die de speler krijgt.
     */
    void setCharacter(const Character &value);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_PROFILE_SCENE_H
