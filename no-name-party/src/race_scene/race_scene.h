//
// Created by tiele on 9/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "../enums/character.h"

#include "car.h"

class RaceScene : public Scene {
private:
    std::unique_ptr<Background> background_tiles;
    std::vector<std::unique_ptr<Sprite>> bombs;
    std::unique_ptr<Car> car;

    bool a_last = true, b_last = true;
    bool a_now = true, b_now = true;

    bool left_last = false, right_last = false;
    bool left_now = false, right_now = false;

    int xCo = GBA_SCREEN_WIDTH / 2, yCo = GBA_SCREEN_HEIGHT / 2;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;

public:
    RaceScene(const std::shared_ptr<GBAEngine> &engine, Character character);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    void placeBombs();

    void goLeft();

    void goRight();

    void moveTo();

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

#endif //GBA_SPRITE_ENGINE_PROJECT_RACE_SCENE_H
