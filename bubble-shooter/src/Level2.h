//
// Created by 11401165 on 21/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL2_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL2_H
#include "SceneLevel1.h"


class Level2: public SceneLevel1 {
private:
    std:: unique_ptr<Sprite> Brick;
    std::vector<std::unique_ptr<Sprite>> wall;
    std::vector<Sprite *> sprites() override;

    int person_side_of_wall();
    void createWall();
    void ball_collides_wall();
    void check_open_wall();
    bool check_allowed_move_person(int direction);
    bool person_collides_wall();
    void tick(u16 keys) override;
    void load()override;
    void atStartGame() override;
    void movePerson(u16 keys) override;
public:
    Level2(std::shared_ptr<GBAEngine> engine, int start_score): SceneLevel1(engine,start_score) {}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL2_H
