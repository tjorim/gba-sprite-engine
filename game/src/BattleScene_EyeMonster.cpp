//
// Created by Florian on 3/01/2019.
//

#include <libgba-sprite-engine/background/background.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "BattleScene_EyeMonster.h"
#include "Adventurer.h"
#include "Background_1.h"
#include "EyeballMonster.h"
#include "DeathScene.h"
#include "BattleScene_Ghost.h"
#include "Victory_Scene.h"


int counter;
std::vector<Background *> BattleScene_EyeMonster::backgrounds() {

    return {background.get()
    };
}

std::vector<Sprite *> BattleScene_EyeMonster::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(adventurer_object->getAdventurerSprite());
    sprites.push_back(adventurer_object->getHealthbar());
    sprites.push_back(eyeball_object->getEyeballSprite());


    return {sprites};
    };


void BattleScene_EyeMonster::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg1Pal, sizeof(bg1Pal)));

    SpriteBuilder<Sprite> builder;

    adventurer = builder
            .withData(adventurer_Tiles, sizeof(adventurer_Tiles))
            .withSize(SIZE_32_32)
            .withAnimated(8,10)
            .withLocation(50,100)
            .withinBounds()
            .buildPtr();
    adventurer->animateToFrame(0);
    adventurer->stopAnimating();


    eyeball = builder
            .withData(eyemonster_Tiles, sizeof(eyemonster_Tiles))
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
    eyeball_object = std::unique_ptr<EyeballMonster>(new EyeballMonster(std::move(eyeball)));
    background = std::unique_ptr<Background>(new Background(0, bg1Tiles, sizeof(bg1Tiles), bg1Map, sizeof(bg1Map)));
    background.get()->useMapScreenBlock(24);

}

void BattleScene_EyeMonster::tick(u16 keys) {
    adventurer_object->tick(keys);
    eyeball_object->tick(keys);



    if (adventurer_object->getAlive() == true){

        if(keys & KEY_LEFT){
            scrollX -= 1;
            background.get()->scroll(scrollX, scrollY);
        }
        if(keys & KEY_RIGHT){
            scrollX += 1;
            background.get()->scroll(scrollX, scrollY);
        }
        if (adventurer_object->getAdventurerSprite()->collidesWith(*eyeball_object->getEyeballSprite())) {
            if (keys & KEY_A) {
                eyeball_object->getEyeballSprite()->moveTo(450, 100);
                counter++;
            } else {
                eyeball_object->getEyeballSprite()->moveTo(450, 100);
                adventurer_object->setLifePoints(adventurer_object->getLifePoints() - 10);
            }
        }

        if (counter >= 4) {
            if (!engine->isTransitioning()) {
                engine->transitionIntoScene(new BattleScene_Ghost(engine), new FadeOutScene(2));
                counter = 0;
            }
        }

    }

    else{
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new DeathScene(engine), new FadeOutScene(4));
            counter = 0;
        }
    }
}