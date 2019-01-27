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

GameScene::GameScene(const std::shared_ptr <GBAEngine> &engine, int level) : Scene(engine), level(level) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector < Sprite * > sprites;

    sprites.push_back(bomSprite.get());
    for (auto &bomb : bombs) {
        sprites.push_back(bomb->getSprite());
    }
/*
    for(auto& rows: board) // Iterating over rows
    {
        for(auto& elem: rows)
        {
            // do some stuff
            sprites.push_back(elem.getSprite());
        }
    }
    */
    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 12, 1);
    return sprites;
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(kruitPal, sizeof(kruitPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr < SpriteBuilder < Sprite >> (new SpriteBuilder <Sprite>);
    // SpriteBuilder<Sprite> spriteBuilder;

    bomSprite = spriteBuilder
            ->withData(kruitTiles, sizeof(kruitTiles))
            .withSize(SIZE_16_16)
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
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
                std::unique_ptr<Bomb>(new Bomb(
                        spriteBuilder->withLocation(2, 2).withVelocity(3, 3).buildWithDataOf(*bomSprite.get()))));
        TextStream::instance().setText(std::string("Boms ") + std::to_string(bombs.size()), 10, 1);
        engine.get()->updateSpritesInScene();

        // Dynamically add the sprite
        // addSprite(bombs[0]->getSprite());
        // but there is no easy way to remove it
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