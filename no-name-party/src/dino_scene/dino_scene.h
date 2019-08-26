//
// Created by tiele on 15/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DINO_SCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_DINO_SCENE_H

#include <libgba-sprite-engine/scene.h>

#include "../enums/character.h"

#include "dino.h"
#include "game_result.h"
#include "../game_scene/player.h"

class DinoScene : public Scene {
private:
    std::unique_ptr <Background> background_clouds;
    std::vector <std::unique_ptr<Sprite>> plants;
    std::unique_ptr <Dino> dino;
    std::unique_ptr<GameResult> game_result;
    std::shared_ptr<Player> player;

    bool fire_last = true, fire_now = true;

    int xCo = 0, yCo = GBA_SCREEN_HEIGHT - 16;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;

public:
    DinoScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player);

    std::vector<Sprite *> sprites() override;

    std::vector<Background *> backgrounds() override;

    void load() override;

    void tick(u16 keys) override;

    void placePlants();

    void jump();

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

#endif //GBA_SPRITE_ENGINE_PROJECT_DINO_SCENE_H
