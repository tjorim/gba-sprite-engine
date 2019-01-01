//
// Created by aydoganmusa on 22.11.18.
//

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "fighting_scene.h"
#include "goku_spritedata.h"
#include "yamcha_spritedata.h"
#include "lifebar_spritedata.h"
#include "energybar_spritedata.h"
#include "wave_spritedata.h"
#include "shared.h"
#include "tournament.h"
#include "attack0.h"
#include "attack1.h"
#include "victory.h"
#include "blast_fullpower.h"


std::vector<Sprite *> FightingScene::sprites() {
    std::vector<Sprite *> sprites;
    sprites.push_back(goku_object->getSpriteWaveGoku());
    sprites.push_back(goku_object->getSpriteGoku());
    sprites.push_back(yamcha_object->getSpriteYamcha());
    sprites.push_back(goku_object->getSpriteLifebarGoku());
    sprites.push_back(yamcha_object->getSpriteLifebarYamcha());
    sprites.push_back(goku_object->getSpriteEnergybarGoku());
    sprites.push_back(yamcha_object->getSpriteEnergybarYamcha());
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
            .withAnimated(6, 3)
            .withLocation(16, GBA_SCREEN_HEIGHT / 2 + 32)
            .withinBounds()
            .buildPtr();
    goku->animateToFrame(0);
    goku->stopAnimating();

    yamcha = Builder
            .withData(yamchaTiles, sizeof(yamchaTiles))
            .withSize(SIZE_32_32)
            .withAnimated(2, 3)
            .withLocation(GBA_SCREEN_WIDTH - 32, GBA_SCREEN_HEIGHT / 2 + 32)
            .withinBounds()
            .buildPtr();
    yamcha->animateToFrame(1);
    yamcha->stopAnimating();

    lifebar_yamcha = Builder
            .withData(lifebarTiles, sizeof(lifebarTiles))
            .withSize(SIZE_32_8)
            .withAnimated(4, 3)
            .withLocation(GBA_SCREEN_WIDTH - 36, 12)
            .withinBounds()
            .buildPtr();
    lifebar_yamcha->animateToFrame(0);
    lifebar_yamcha->stopAnimating();

    lifebar_goku = Builder
            .withData(lifebarTiles, sizeof(lifebarTiles))
            .withSize(SIZE_32_8)
            .withAnimated(4, 3)
            .withLocation(4, 12)
            .withinBounds()
            .buildPtr();
    lifebar_goku->animateToFrame(0);
    lifebar_goku->stopAnimating();

    energybar_goku = Builder
            .withData(energybarTiles, sizeof(energybarTiles))
            .withSize(SIZE_32_8)
            .withAnimated(4, 3)
            .withLocation(4, 20)
            .withinBounds()
            .buildPtr();
    energybar_goku->animateToFrame(0);
    energybar_goku->stopAnimating();

    energybar_yamcha = Builder
            .withData(energybarTiles, sizeof(energybarTiles))
            .withSize(SIZE_32_8)
            .withAnimated(4, 3)
            .withLocation(GBA_SCREEN_WIDTH - 36, 20)
            .withinBounds()
            .buildPtr();
    energybar_yamcha->animateToFrame(0);
    energybar_yamcha->stopAnimating();

    wave = Builder
            .withData(waveTiles, sizeof(waveTiles))
            .withSize(SIZE_64_32)
            .withLocation(-64, -32)
            .withinBounds()
            .buildPtr();

    bg = std::unique_ptr<Background>(
            new Background(0, tournamentTiles, sizeof(tournamentTiles), tournamentMap, sizeof(tournamentMap)));
    bg.get()->useMapScreenBlock(20);

    yamcha_object = std::unique_ptr<Yamcha>(
            new Yamcha(std::move(yamcha), std::move(lifebar_yamcha), std::move(energybar_yamcha)));
    goku_object = std::unique_ptr<Goku>(
            new Goku(std::move(goku), std::move(lifebar_goku), std::move(wave), std::move(energybar_goku)));
}

void FightingScene::tick(u16 keys) {

    if (gameEnd) {
        if (keys & KEY_START) {
            goku_object->resetGoku();
            yamcha_object->resetYamcha();
            engine->enqueueSound(victory_sound, sizeof(victory_sound), 15700);
            gameEnd = false;
        }
    } else {
        goku_object->tick();
        yamcha_object->tick();
        if (keys & KEY_LEFT) {
            if (!(goku_object->getMoveLeft())) {
                goku_object->setMoveLeft(true);
            }
        } else if (keys & KEY_RIGHT) {
            if (!(goku_object->getMoveRight())) {
                goku_object->setMoveRight(true);
            }
        } else if (keys & KEY_A) {
            if (!(goku_object->getHit())) {
                goku_object->setHit(true);
                engine->enqueueSound(attack0_sound, sizeof(attack0_sound), 15768);
            } else {
                if (goku_object->getSpriteGoku()->collidesWith(*(yamcha_object->getSpriteYamcha()))) {
                    yamcha_object->gotHurt();
                }
            }
        } else if (keys & KEY_B) {
            if (!(goku_object->getKick())) {
                goku_object->setKick(true);
                engine->enqueueSound(attack1_sound, sizeof(attack1_sound), 15768);
            } else {
                if (goku_object->getSpriteGoku()->collidesWith(*(yamcha_object->getSpriteYamcha()))) {
                    yamcha_object->gotHurt();
                }
            }
        } else if (keys & KEY_UP) {
            if (goku_object->getSpriteWaveGoku()->collidesWith(*(yamcha_object->getSpriteYamcha()))) {
                yamcha_object->gotHurt();
            }
            if (goku_object->getSpecialAttack()) {
                engine->enqueueSound(blast_fullpower, sizeof(blast_fullpower), 15768);
                goku_object->setChargeSpecialAttack(false);
            } else {
                goku_object->setChargeSpecialAttack(true);
            }
        } else if (yamcha_object->isdood() || goku_object->getDood()) {
            gameEnd = true;
            return;
        } else {
            goku_object->setMoveLeft(false);
            goku_object->setMoveRight(false);
            goku_object->setHit(false);
            goku_object->setKick(false);
            goku_object->setChargeSpecialAttack(false);
            goku_object->setSpecialAttack(false);
            yamcha_object->notGotHurt();
        }
    }
}