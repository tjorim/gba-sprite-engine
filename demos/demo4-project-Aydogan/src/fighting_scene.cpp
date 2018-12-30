//
// Created by aydoganmusa on 22.11.18.
//


#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "fighting_scene.h"
#include "goku_spritedata.h"
#include "yamcha_spritedata.h"
#include "shared.h"
#include "tournament.h"


std::vector<Sprite *> FightingScene::sprites() {
    std::vector<Sprite *> sprites;
    sprites.push_back(goku_object->getSprite());
    sprites.push_back(yamcha_object->getSprite());
    return {sprites};
}

std::vector<Background *> FightingScene::backgrounds() {
    return {bg.get()};
}

void FightingScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(tournamentPal, sizeof(tournamentPal)));
    SpriteBuilder<Sprite> Builder;

    goku = Builder
            .withData(gokuTiles, sizeof(gokuTiles))
            .withSize(SIZE_32_32)
            .withAnimated(5, 3)
            .withLocation(16, GBA_SCREEN_HEIGHT / 2 + 32)
            .withinBounds()
            .buildPtr();
    goku->animateToFrame(0);
    goku->stopAnimating();
    goku_object = std::unique_ptr<Goku>(new Goku(std::move(goku)));

    yamcha = Builder
            .withData(yamchaTiles, sizeof(yamchaTiles))
            .withSize(SIZE_32_32)
            .withAnimated(2, 3)
            .withLocation(GBA_SCREEN_WIDTH - 32, GBA_SCREEN_HEIGHT / 2 + 32)
            .withinBounds()
            .buildPtr();
    yamcha->animateToFrame(1);
    yamcha->stopAnimating();
    yamcha_object = std::unique_ptr<Yamcha>(new Yamcha(std::move(yamcha)));
    bg = std::unique_ptr<Background>(
            new Background(0, tournamentTiles, sizeof(tournamentTiles), tournamentMap, sizeof(tournamentMap)));
    bg.get()->useMapScreenBlock(26);
}

void FightingScene::tick(u16 keys) {
    goku_object->tick();
    yamcha_object->tick();
    if (keys & KEY_LEFT) {
        goku_object->doMoveLeft();
    } else if (keys & KEY_RIGHT) {
        goku_object->doMoveRight();
    } else if (keys & KEY_A) {
        goku_object->doHit();
        if (goku_object->getSprite()->collidesWith(*(yamcha_object->getSprite()))) {
            yamcha_object->gotHurt();
        }
    } else if (keys & KEY_B) {
        goku_object->doKick();
        if (goku_object->getSprite()->collidesWith(*(yamcha_object->getSprite()))) {
            yamcha_object->gotHurt();
        }
    }else {
        goku_object->doNotMoveLeft();
        goku_object->doNotMoveRight();
        goku_object->doNotHit();
        goku_object->doNotKick();
        yamcha_object->notGotHurt();
    }
}
