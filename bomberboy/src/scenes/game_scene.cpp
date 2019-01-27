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

GameScene::GameScene(const std::shared_ptr<GBAEngine> &engine, int level) : Scene(engine), level(level) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(bompje.get());
/*
    for(auto& bomb : bombs)
    {
        sprites.push_back(bomb->getSprite());
    }
    */
    
    /*
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            sprites.push_back(board[i][j].getSprite());
        }
    }
    */
    return sprites;
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);
    // SpriteBuilder<Sprite> spriteBuilder;

    bomSprite = spriteBuilder
            ->withData(bullet_data, sizeof(bullet_data))
            .withSize(SIZE_16_16)
            .withLocation(10, 10)
            .buildPtr();
    
    bompje = spriteBuilder
            ->withData(bullet_data, sizeof(bullet_data))
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
            std::unique_ptr<Bomb>(new Bomb(spriteBuilder->buildWithDataOf(*bomSprite.get()))));
            TextStream::instance().setText(std::string("Bom ") + std::to_string(bombs.size()), 10, 1);
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