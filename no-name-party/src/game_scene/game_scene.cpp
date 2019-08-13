//
// Created by Jorim Tielemans
//

#include <math.h>

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "../end_scene/end_scene.h"
#include "../book_scene/book_scene.h"

#include "../enums/character.h"
#include "../enums/result.h"

#include "background/background_map.h"
#include "foreground/sprites/shared_game_scene.h"

GameScene::GameScene(const std::shared_ptr<GBAEngine> &engine, int character) : Scene(engine), character(character) {}

std::vector<Background *> GameScene::backgrounds() {
    return {
            background_map.get()
    };
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(player->getSprite());
    //sprites.push_back(result->getSprite());

    /*
    for(auto& rows: board) // Iterating over rows
    {
        for(auto& elem: rows)
        {
            // do some stuff
            sprites.push_back(elem->getSprite());
        }
    }
    */

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void GameScene::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_mapPal, sizeof(background_mapPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_game_scenePal, sizeof(shared_game_scenePal)));

    background_map = std::unique_ptr<Background>(
            new Background(1, background_mapTiles, sizeof(background_mapTiles),
                           background_mapMap, sizeof(background_mapMap)));
    background_map->useMapScreenBlock(16);

    player = std::unique_ptr<Player>(new Player(static_cast<Character>(getCharacter()), xCoPlayer, yCoPlayer));
    //result = std::unique_ptr<GameResult>(new GameResult(static_cast<Character>(getCharacter()), Result::LOSE));

/*
    for (int i = 0; i < BOARD_WIDTH; i++) { // board.size(), Iterating over rows
        for (int j = 0; j < BOARD_HEIGHT; j++) { // board[i].size()
            if(i == 0 || i == BOARD_WIDTH-1 || j == 0 || j == BOARD_HEIGHT-1) {
                board[i][j] = new Wall(i, j);
            } else {
                board[i][j] = new Floor(i, j);
            }
        }
    }
*/

    engine->getTimer()->start();
    // engine->enqueueMusic(cataclysmic_molten_core, sizeof(cataclysmic_molten_core));

    //EndScene *endScene = new EndScene(engine);
    //BookScene *bookScene = new BookScene(engine);
}

void GameScene::tick(u16 keys) {

    /*
    if (player->isDood()) {
        engine->setScene(new EndScene(engine));
    }
    */

    /*if (keys & KEY_FIRE) {
        //dropBomb();
    } else*/ if (keys & KEY_A) {
        player->scoreHoger();
        //engine->dequeueAllSounds();
        //engine->enqueueMusic(Title_Screen_wav, sizeof(Title_Screen_wav));
    } else if (keys & KEY_B) {
        //engine->setScene(new BookScene(engine));
        //result = std::unique_ptr<GameResult>(new GameResult(static_cast<Character>(getCharacter()), Result::WIN));
        //engine->updateSpritesInScene();
    } else if (keys & KEY_UP) {
        moveUp();
    } else if (keys & KEY_DOWN) {
        moveDown();
    } else if (keys & KEY_LEFT) {
        moveLeft();
    } else if (keys & KEY_RIGHT) {
        moveRight();
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
    TextStream::instance().setText(std::string("Game scene"), 0, 0);
    TextStream::instance().setText(std::string("Score ") + std::to_string(player->getScore()), 0, 21);
}

int GameScene::getCharacter() const {
    return character;
}

/*
thingType GameScene::getThingType(int xValue, int yValue) {
    thingType type = board[xValue][yValue]->getType();
    TextStream::instance().setText(std::string("Type: ") + std::to_string(
        static_cast<std::underlying_type<thingType>::type>(type)
        ), 13, 1);
    return type;
}
*/

/*
void GameScene::dropBomb() {
    if(player->getAantalBommen() > 0) {
        int bombX = player->getXCoGrid();
        int bombY = player->getYCoGrid();
        thingType thingUnderPlayerType = getThingType(bombX, bombY);

        if(thingUnderPlayerType == thingType::FLOOR || thingUnderPlayerType == thingType::GUNPOWDER) {
            bombs.push_back(std::unique_ptr<Bomb>(new Bomb(bombX, bombY)));
            // Dynamically add the sprite
            //addSprite(bombs.back()->getSprite());
            // but there is no easy way to remove it
            engine.get()->updateSpritesInScene();
            TextStream::instance().setText(std::string("Boms ") + std::to_string(bombs.size()), 10, 1);
            player->eenBomMinder();
        }
    }
    */

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
}
*/

void GameScene::moveMapTo(int xValue, int yValue) {
    setXCoMap(xValue);
    setYCoMap(yValue);

    background_map->scroll(xValue, yValue);
}

void GameScene::movePlayerTo(int xValue, int yValue) {
    setXCoPlayer(xValue);
    setYCoPlayer(yValue);

    player->moveTo(xValue, yValue);
}

int GameScene::getXCo() const {
    return xCoMap + xCoPlayer;
}

int GameScene::getYCo() const {
    return yCoMap + yCoPlayer;
}

int GameScene::getXCoRelative() const {
    return std::round(float(getXCo() - 40) / 32);
}

int GameScene::getYCoRelative() const {
    return std::round(float(getYCo() - 40) / 32);
}

/**
 * Beweeg 1 vakje naar boven.
 */
void GameScene::moveUp() {
    player->setDirection(Direction::UP);

    if (yCoMap > 0) {
        moveMapTo(xCoMap, yCoMap - 1);
    } else if (yCoPlayer > 40) {
        movePlayerTo(xCoPlayer, yCoPlayer - 2);
    }

    engine->updateSpritesInScene();
    //moveRelative(0, -1);
}

/**
 * Beweeg 1 vakje naar onder.
 */
void GameScene::moveDown() {
    player->setDirection(Direction::DOWN);

    if (yCoMap < 112) {
        moveMapTo(xCoMap, yCoMap + 1);
    } else if (yCoPlayer < 88) {
        movePlayerTo(xCoPlayer, yCoPlayer + 2);
    }

    engine->updateSpritesInScene();
    //moveRelative(0, 1);
}

/**
 * Beweeg 1 vakje naar links.
 */
void GameScene::moveLeft() {
    player->setDirection(Direction::LEFT);

    if (xCoMap > 0) {
        moveMapTo(xCoMap - 1, yCoMap);
    } else if (xCoPlayer > 40) {
        movePlayerTo(xCoPlayer - 2, yCoPlayer);
    }

    engine->updateSpritesInScene();
    //moveRelative(-1, 0);
}

/**
 * Beweeg 1 vakje naar rechts.
 */
void GameScene::moveRight() {
    player->setDirection(Direction::RIGHT);

    if (xCoMap < 32) {
        moveMapTo(xCoMap + 1, yCoMap);
    } else if (xCoPlayer < 168) {
        movePlayerTo(xCoPlayer + 2, yCoPlayer);
    }

    engine->updateSpritesInScene();
    //moveRelative(1, 0);
}

int GameScene::getXCoMap() const {
    return xCoMap;
}

void GameScene::setXCoMap(int value) {
    xCoMap = value;
}

int GameScene::getYCoMap() const {
    return yCoMap;
}

void GameScene::setYCoMap(int value) {
    yCoMap = value;
}

int GameScene::getXCoPlayer() const {
    return xCoPlayer;
}

void GameScene::setXCoPlayer(int value) {
    xCoPlayer = value;
}

int GameScene::getYCoPlayer() const {
    return yCoPlayer;
}

void GameScene::setYCoPlayer(int value) {
    yCoPlayer = value;
}