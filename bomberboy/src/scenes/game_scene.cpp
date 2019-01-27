//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "end_scene.h"
#include "../thing/bomb.h"
#include "../../img/bullet_data.h"
#include "../../img/avatar.h"
#include "../../img/kruit.h"

GameScene::GameScene(const std::shared_ptr<GBAEngine> &engine, int level) : Scene(engine), level(level) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector<Sprite *> sprites;

    //sprites.push_back(bompje.get());

    for(int i = 0; i < bombs.size(); ++i)
    {
        sprites.push_back(bombs[i]->getSprite());
    }
    
    ++testCounter;
    /*
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            sprites.push_back(board[i][j].getSprite());
        }
    }
    */
    sprites.push_back(bomSprite.get());
    TextStream::instance().setText(std::string("Counter ") + std::to_string(testCounter), 11, 1);
    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 12, 1);
    return sprites;
    //return {bompje.get()};
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(kruitPal, sizeof(kruitPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    // SpriteBuilder<Sprite> spriteBuilder;

    bomSprite = spriteBuilder
            ->withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();
    
    bompje = spriteBuilder
            ->withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_16_16)
            .withLocation(10, 10)
            .buildPtr();

/*
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            board[i][j] = new Thing();
            //cout << board[i][j] << " ";
        }
        //cout << endl;
    }
*/
    // engine->getTimer()->start();
    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));

    // EndScene *endScene = new EndScene(engine);
}

void GameScene::tick(u16 keys) {
    TextStream::instance().setText(std::string("Game scene"), 5, 1);

    if (keys & KEY_ACCEPT) {
        bombs.push_back(
            std::unique_ptr<Bomb>(new Bomb(spriteBuilder->withLocation(2,2).withVelocity(3,3).buildWithDataOf(*bomSprite.get()))));
             TextStream::instance().setText(std::string("Bom ") + std::to_string(bombs.size()), 10, 1);
        // bombs.push_back(std::unique_ptr<Bomb>(new Bomb(spriteBuilder
        //     ->withData(kruitTiles, sizeof(kruitTiles))
        //     .withSize(SIZE_16_16)
        //     .withLocation(10, 10)
        //     .withVelocity(1,1)
        //     .buildPtr())));
        engine.get()->updateSpritesInScene();
        //addSprite(bombs[0]->getSprite());
    }
    /*
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine, getLevel()));
    } else if (keys & KEY_LEFT) {
        playerLeft();
    } else if (keys & KEY_RIGHT) {
        playerRight();
    } else if (keys & KEY_DOWN) {
        playerDown();
    } else if (keys & KEY_UP) {
        playerUp();
    }
    /*
    if(engine->getTimer()->getTotalMsecs() < 5000) {
        counter++;
    } else {
        engine->getTimer()->stop();
    }

    TextStream::instance().setText(std::to_string(counter) + std::string(" frames/5sec"), 5, 1);
    TextStream::instance().setText(std::string(engine->getTimer()->to_string()), 6, 1);
    */
}