//
// Created by JT
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "test_scene.h"
#include "sound.h"

std::vector<Background *> TestScene::backgrounds() {
    return {};
}

std::vector<Sprite *> TestScene::sprites() {
    return {player.get()};
}

void TestScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));
    // backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    Dude* dude = new Dude(50, 50);

    player = builder
            .withSize(SIZE_8_8)
            .withLocation((u32) dude->getX(), (u32) dude->getY())
            .withData(ballTiles, sizeof(ballTiles))
            .withVelocity(0, 0)
            .buildPtr();

    dude->setView(player.get());

    controller = new PlayerController();
    controller->setModel(dude);

    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void TestScene::tick(u16 keys) {

    if(keys && KEY_UP) {
        //player->moveTo(player->getX(), player->getY() + 10);
        // player->setVelocity(10,10);
    }

    controller->processKeys(keys);

    //TextStream::instance().setText(std::to_string(counter) + std::string(" frames/5sec"), 5, 1);
    //TextStream::instance().setText(std::string(engine->getTimer()->to_string()), 6, 1);
 }