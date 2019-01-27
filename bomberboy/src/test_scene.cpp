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
    std::vector<Sprite*> sprites;
    sprites.push_back(_player.get());
    for (int i = 0; i < _bullets.size(); ++i) {
        sprites.push_back(_bullets[i]);
    }
    return sprites;
}

void TestScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(paletteSharedPal, sizeof(paletteSharedPal)));
    // backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    SpriteBuilder<Sprite> builder;

    _model = new Dude(50, 50);

    _player = builder
            .withSize(SIZE_8_8)
            .withLocation((u32) _model->getX(), (u32) _model->getY())
            .withData(ballTiles, sizeof(ballTiles))
            .withVelocity(0, 0)
            .buildPtr();

    _bulletSprite = builder
            .withSize(SIZE_16_8)
            .withData(block_greenTiles, sizeof(block_greenTiles))
            .buildPtr();

    _model->setView(_player.get());

    _controller = new PlayerController();
    _controller->setModel(_model);

    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));
}

void TestScene::tick(u16 keys) {

    _controller->processKeys(keys);

    updateFromModel();

    //TextStream::instance().setText(std::to_string(counter) + std::string(" frames/5sec"), 5, 1);
    //TextStream::instance().setText(std::string(engine->getTimer()->to_string()), 6, 1);
 }

 void TestScene::updateFromModel() {
    SpriteBuilder<Sprite> builder;
    BaseData* data = _model->getData();
    PlayerData* playerData = dynamic_cast<PlayerData*>(data);
    if (playerData != nullptr) {
        Bullet** bullets = playerData->getBullets();
        int n = playerData->getInt();
        _bullets.clear();
        for(int i = 0; i < n; ++i) {
            bullets[i]->setView(builder.buildWithDataOf(*_bulletSprite.get()).get());
            _bullets.push_back(bullets[i]->getView());
        }
    }
}