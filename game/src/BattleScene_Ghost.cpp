//
// Created by Florian on 26/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "BattleScene_Ghost.h"
#include "Scene_2.h"
#include "DeathScene.h"
#include "Victory_Scene.h"

int counter2;
std::vector<Background *> BattleScene_Ghost::backgrounds() {

    return {background.get()
    };
}

std::vector<Sprite *> BattleScene_Ghost::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(adventurer_object->getAdventurerSprite());
    sprites.push_back(adventurer_object->getHealthbar());
    sprites.push_back(ghost_object->getGhostSprite());


    return {sprites};
};


void BattleScene_Ghost::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg2Pal, sizeof(bg2Pal)));

    SpriteBuilder<Sprite> builder;

    adventurer = builder
            .withData(adventurerTiles, sizeof(adventurerTiles))
            .withSize(SIZE_32_32)
            .withAnimated(8,10)
            .withLocation(50,100)
            .withinBounds()
            .buildPtr();
    adventurer->animateToFrame(0);
    adventurer->stopAnimating();


    ghost = builder
            .withData(GhostTiles, sizeof(GhostTiles))
            .withSize(SIZE_32_32)
            .withAnimated(4,10)
            .withLocation(150,100)
            .buildPtr();




    healthbar = builder
            .withData(healthbarTiles, sizeof(healthbarTiles))
            .withSize(SIZE_32_8)
            .withAnimated(5,15)
            .withLocation(10,10)
            .buildPtr();
    healthbar->stopAnimating();



    adventurer_object = std::unique_ptr<Adventurer>(new Adventurer(std::move(adventurer), std::move(healthbar)));
    ghost_object = std::unique_ptr<Ghost>(new Ghost(std::move(ghost)));
    background = std::unique_ptr<Background>(new Background(0, bg2Tiles, sizeof(bg2Tiles), bg2Map, sizeof(bg2Map)));
    background.get()->useMapScreenBlock(24);

}

void BattleScene_Ghost::tick(u16 keys) {
    adventurer_object->tick(keys);
    ghost_object->tick(keys);


    if (adventurer_object->getAlive() == true) {

        if (keys & KEY_LEFT) {
            scrollX -= 1;
            background.get()->scroll(scrollX, scrollY);
        }
        if (keys & KEY_RIGHT) {
            scrollX += 1;
            background.get()->scroll(scrollX, scrollY);
        }
        if (adventurer_object->getAdventurerSprite()->collidesWith(*ghost_object->getGhostSprite())) {
            if (keys & KEY_A) {
                ghost_object->getGhostSprite()->moveTo(450, 100);
                counter2++;
            } else {
                ghost_object->getGhostSprite()->moveTo(450, 100);
                adventurer_object->setLifePoints(adventurer_object->getLifePoints() - 10);
            }
        }

        if (counter2 >= 4) {
            if (!engine->isTransitioning()) {
                engine->transitionIntoScene(new Victory_Scene(engine), new FadeOutScene(2));
                counter2 = 0;
            }
        }

    } else {
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new DeathScene(engine), new FadeOutScene(4));
            counter2 = 0;
        }
    }
}