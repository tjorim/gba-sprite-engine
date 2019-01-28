//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "end_scene.h"
#include "../thing/bomb.h"
#include "../thing/player.h"
#include "../thing/solid/crate.h"
#include "../thing/solid/wall.h"
#include "../thing/surface/floor.h"
#include "../thing/surface/gunpowder.h"
#include "../thing/surface/portal.h"
#include "../thing/surface/power_up.h"
#include "../../sprites/blauw_boven.h"
#include "../../sprites/shared.h"

GameScene::GameScene(const std::shared_ptr <GBAEngine> &engine, int level) : Scene(engine), level(level) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector < Sprite * > sprites;

    for (auto &bomb : bombs) {
        sprites.push_back(bomb->getSprite());
    }

    sprites.push_back(player1->getSprite());

    for(auto& rows: board) // Iterating over rows
    {
        for(auto& elem: rows)
        {
            // do some stuff
            sprites.push_back(elem->getSprite());
        }
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 12, 1);
    return sprites;
}

void GameScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    spriteBuilder = std::unique_ptr < SpriteBuilder < Sprite >> (new SpriteBuilder <Sprite>);
    // SpriteBuilder<Sprite> spriteBuilder;

    bombSprite = spriteBuilder
            ->withData(blauw_bovenTiles, sizeof(blauw_bovenTiles))
            .withSize(SIZE_8_16)
            .withinBounds()
            .withLocation(GBA_SCREEN_WIDTH + 20, GBA_SCREEN_HEIGHT + 20)
            .buildPtr();

    player1 = std::unique_ptr<Player>(new Player(5, 5));

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
        bombs.push_back(std::unique_ptr<Bomb>(new Bomb(10, 10)));
        TextStream::instance().setText(std::string("Boms ") + std::to_string(bombs.size()), 10, 1);
        engine.get()->updateSpritesInScene();

        // Dynamically add the sprite
        // addSprite(bombs[0]->getSprite());
        // but there is no easy way to remove it
    }
    /*
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine, getLevel()));
    } */else if (keys & KEY_LEFT) {
        player1->move(player1->getXCo()-1, player1->getYCo());
        //playerLeft();
    } else if (keys & KEY_RIGHT) {
        player1->move(player1->getXCo()+1, player1->getYCo());
        //playerRight();
    } else if (keys & KEY_DOWN) {
        player1->move(player1->getXCo(), player1->getYCo()+1);
        //playerDown();
    } else if (keys & KEY_UP) {
        player1->move(player1->getXCo(), player1->getYCo()+1);
        //playerUp();
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