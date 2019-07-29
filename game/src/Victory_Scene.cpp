//
// Created by Florian on 27/01/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "Victory_Scene.h"
#include "victory_data.h"
#include "Victory.h"


std::vector<Background *> Victory_Scene::backgrounds() {

    return {background.get()
    };
}

std::vector<Sprite *> Victory_Scene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(adventurer_object->getAdventurerSprite());
    sprites.push_back(chalice_object->getChaliceSprite());
    return {sprites};
};


void Victory_Scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(VictoryPal, sizeof(VictoryPal)));

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

    chalice = builder
            .withData(chaliceTiles, sizeof(chaliceTiles))
            .withSize(SIZE_32_32)
            .withLocation(200,100)
            .buildPtr();

    adventurer_object = std::unique_ptr<Adventurer>(new Adventurer(std::move(adventurer)));
    chalice_object = std::unique_ptr<Chalice>(new Chalice(std::move(chalice)));

    background = std::unique_ptr<Background>(new Background(0, VictoryTiles, sizeof(VictoryTiles), VictoryMap, sizeof(VictoryMap)));
    background.get()->useMapScreenBlock(20);

}

void Victory_Scene::tick(u16 keys) {
    adventurer_object->tick(keys);

    if (adventurer_object->getAdventurerSprite()->collidesWith(*chalice_object->getChaliceSprite())) {
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new Victory(engine), new FadeOutScene(1));
        }
    }

}
