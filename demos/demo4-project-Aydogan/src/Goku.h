//
// Created by aydoganmusa on 29.12.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GOKU_H
#define GBA_SPRITE_ENGINE_PROJECT_GOKU_H

#include <libgba-sprite-engine/gba/tonc_math.h>
#include <libgba-sprite-engine/sprites/sprite.h>


class Goku {

private:
    std::unique_ptr<Sprite> goku;
    std::unique_ptr<Sprite> lifebar;
    std::unique_ptr<Sprite> energybar;
    std::unique_ptr<Sprite> wave;
    bool moveLeft = false;
    bool moveRight = false;
    bool kick = false;
    bool hit = false;
    bool specialAttack = false;
    bool charge = false;
    bool omkeren = false;
    bool dood = false;
    int levenspunten = 300;
    int energypunten = 300;
    int charging = 0;

public:
    Goku(std::unique_ptr<Sprite> sprite1, std::unique_ptr<Sprite> sprite2, std::unique_ptr<Sprite> sprite3,
         std::unique_ptr<Sprite> sprite4) : goku(std::move(sprite1)), lifebar(std::move(sprite2)),
                                            wave(std::move(sprite3)), energybar(std::move(sprite4)) {};

    void doChargeSpecialAttack();

    void doNotChargeSpecialAttack();

    void doSpecialAttack();

    void doNotSpecialAttack();

    void doMoveLeft();

    void doNotMoveLeft();

    void doMoveRight();

    void doNotMoveRight();

    void doKick();

    void doNotKick();

    void doHit();

    void doNotHit();

    void setDood(bool input);

    bool isdood();

    void tick();

    Sprite *getSpriteGoku() { return goku.get(); }

    Sprite *getSpriteLifebarGoku() { return lifebar.get(); }

    Sprite *getSpriteEnergybarGoku() { return energybar.get(); }

    Sprite *getSpriteWaveGoku() { return wave.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GOKU_H
