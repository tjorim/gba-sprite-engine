//
// Created by Jorim Tielemans
//

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

    player1 = std::unique_ptr<Player>(new Player(5, 5));

    for (int i = 0; i < BOARD_WIDTH; i++) { // board.size(), Iterating over rows
        for (int j = 0; j < BOARD_HEIGHT; j++) { // board[i].size()
            board[i][j] = new Wall(i, j);
        }
    }

    // engine->getTimer()->start();
    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));

    // EndScene *endScene = new EndScene(engine);
}

void GameScene::tick(u16 keys) {
    TextStream::instance().setText(std::string("Game scene"), 5, 1);

    if (keys & KEY_FIRE) {
        dropBomb();
    } else if (keys & KEY_UP) {
        movePlayerUp();
    } else if (keys & KEY_DOWN) {
        movePlayerDown();
    } else if (keys & KEY_LEFT) {
        movePlayerLeft();
    } else if (keys & KEY_RIGHT) {
        movePlayerRight();
    }
    /*
    if (keys & KEY_ACCEPT) {
        engine->setScene(new GameScene(engine, getLevel()));
    } */
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

void GameScene::movePlayer(int xValue, int yValue) {
    int newX = player1->getXCoSprite()+xValue;
    int newY = player1->getYCoSprite()+yValue;
    player1->move(newX, newY);
}

/**
 * Beweeg 1 vakje naar boven.
 */
void GameScene::movePlayerUp() {
    movePlayer(0,-1);
}

/**
 * Beweeg 1 vakje naar onder.
 */
void GameScene::movePlayerDown() {
    movePlayer(0,1);
}

/**
 * Beweeg 1 vakje naar links.
 */
void GameScene::movePlayerLeft() {
    movePlayer(-1,0);
}

/**
 * Beweeg 1 vakje naar rechts.
 */
void GameScene::movePlayerRight() {
    movePlayer(1,0);
}

Thing * GameScene::getThing(int xValue, int yValue) {
    return board[xValue][yValue];
}

void GameScene::dropBomb() {
    if(player1->getAantalBommen() > 0) {
        int bombX = player1->getXCoGrid();
        int bombY = player1->getYCoGrid();
        thingType thingUnderPlayerType = getThing(bombX, bombY)->getType();

        if(thingUnderPlayerType == thingType::FLOOR || thingUnderPlayerType == thingType::GUNPOWDER) {
            bombs.push_back(std::unique_ptr<Bomb>(new Bomb(bombX, bombY)));
            TextStream::instance().setText(std::string("Boms ") + std::to_string(bombs.size()), 10, 1);
            engine.get()->updateSpritesInScene();
            player1->eenBomMinder();
        }
    }

    // Dynamically add the sprite
    // addSprite(bombs[0]->getSprite());
    // but there is no easy way to remove it

    /*
        if(speler->getThingUnderPlayer()->getType() == Thing::thingType::FLOOR)
        {
            // create a bomb with floor under it
            Bomb *bomb = new Bomb(speler->getPlayerNumber(), new Floor());
            qDebug() << "Bomb created";
            bomb->setPos(speler->getXCo(), speler->getYCo());
            scene->addItem(bomb);
            //speler->setThingUnderPlayer(new Bomb(speler->getPlayerNumber(), new Floor()));
        }
        else if(speler->getThingUnderPlayer()->getType() == Thing::thingType::GUNPOWDER)
        {
            speler->setThingUnderPlayer(new Bomb(speler->getPlayerNumber(), new Gunpowder()));
        }
        
        //speelGeluidje(BombDrop);
    */
}
