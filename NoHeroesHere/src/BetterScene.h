//
// Created by ubuntu on 29.11.18.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BETTERSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_BETTERSCENE_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "Enemy.h"

class BetterScene  : public Scene  {
private:
    std::unique_ptr<Sprite> mooi_sprite;
    std::unique_ptr<Sprite> mooi_sprite1;
    std::unique_ptr<Sprite> eendje;
    std::unique_ptr<Sprite> ladderGroot;
    std::unique_ptr<Sprite> ladderGroot2;
    std::unique_ptr<Sprite> ladderGroot3;
    std::unique_ptr<Sprite> ladderGroot4;
    std::unique_ptr<Sprite> ladderHoofd;
    std::unique_ptr<Sprite> ladderHoofd2;
    std::unique_ptr<Sprite> ladderHoofd3;
    std::unique_ptr<Sprite> gunpowder;
    std::unique_ptr<Sprite> gunpowder2;
    std::unique_ptr<Sprite> bom;
    std::unique_ptr<Sprite> bom2;
    std::unique_ptr<Sprite> kanon;
    std::unique_ptr<Sprite> kanon2;
    std::unique_ptr<Sprite> kogel;
    std::unique_ptr<Sprite> kist;
    std::unique_ptr<Sprite> kist2;
    std::unique_ptr<Background> bg;

    int scrollX, scrollY;
    int prevScrollX, prevScrollY;
    int player1Bom = 0 , player2Bom = 0, player1Gunpowder = 0, player2Gunpowder = 0;
    int kanonBom = 0, kanonGunpowder = 0, kanon2Bom = 0, kanon2Gunpowder = 0;
    int bomVolg = 0, bom2Volg = 0, gunpowderVolg = 0, gunpowder2Volg = 0;
    int health = 250;
    int killCounter = 0;

    bool  switchLock = false;

    //Enemy
    Enemy* enemy;

public:
    BetterScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) , scrollX(0), scrollY(0) {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
    void syncScroll();
    void interactUp(Sprite &sprite , int cPlayer);
    void interactDown(Sprite &sprite, int cPlayer);
    void gameOver();

    int player1TranslationH = 70;
    int player1TranslationV = 105;
    int player2TranslationH = 110;
    int player2TranslationV = 57;
    int currentPlayer = 0;
    int counter=0;

    int eendjeTranslationH = 0;
    int eendjeTranslationV = 0;
    int kistTranslationH = 0;
    int kistTranslationV = 0;
    int ladderHoofdTranslationH = 0;
    int ladderHoofdTranslationV = 0;
    int ladderHoofd2TranslationH = 0;
    int ladderHoofd2TranslationV = 0;
    int ladderHoofd3TranslationH = 0;
    int ladderHoofd3TranslationV = 0;
    int ladderGrootTranslationH = 0;
    int ladderGrootTranslationV = 0;
    int ladderGroot2TranslationH = 0;
    int ladderGroot2TranslationV = 0;
    int kanonTranslationH = 0;
    int kanonTranslationV = 0;
    int kanon2TranslationH = 0;
    int kanon2TranslationV = 0;



};


#endif //GBA_SPRITE_ENGINE_PROJECT_BETTERSCENE_H
