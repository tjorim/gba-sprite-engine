//
// Created by Jorim Tielemans
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "game_scene.h"
#include "../end_scene/end_scene.h"
#include "../enums/character.h"
#include "../enums/result.h"
#include "foreground/sprites/shared_game_scene.h"

int lol = 1;

GameScene::GameScene(const std::shared_ptr<GBAEngine> &engine, int character) : Scene(engine), character(character) {}

std::vector<Background *> GameScene::backgrounds() {
    return {};
}

std::vector<Sprite *> GameScene::sprites() {
    std::vector<Sprite *> sprites;

    sprites.push_back(player->getSprite());
    sprites.push_back(result->getSprite());

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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_game_scenePal, sizeof(shared_game_scenePal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager());
            //new BackgroundPaletteManager(mapPal, sizeof(mapPal)));

    player = std::unique_ptr<Player>(new Player(static_cast<Character>(getCharacter())));
    result = std::unique_ptr<GameResult>(new GameResult(static_cast<Character>(getCharacter()), Result::LOSE));

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

    EndScene *endScene = new EndScene(engine);
}

void GameScene::tick(u16 keys) {

    /*
    if (player->isDood()) {
        engine->setScene(new EndScene(engine));
    }
    */

    if (keys & KEY_FIRE) {
        //dropBomb();
    } else if (keys & KEY_A) {
        //player->setCharacter(Character::LUIGI);
    } else if (keys & KEY_B) {
        //player->setCharacter(Character::PRINCESS_PEACH);
        result = std::unique_ptr<GameResult>(new GameResult(static_cast<Character>(getCharacter()), Result::WIN));
        engine->updateSpritesInScene();
    } else if (keys & KEY_UP) {
        player->moveUp();
        engine->updateSpritesInScene();
    } else if (keys & KEY_DOWN) {
        player->moveDown();
        engine->updateSpritesInScene();
    } else if (keys & KEY_LEFT) {
        player->moveLeft();
        engine->updateSpritesInScene();
    } else if (keys & KEY_RIGHT) {
        player->moveRight();
        engine->updateSpritesInScene();
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
    TextStream::instance().setText(std::string("lollig ") + std::to_string(lol), 2, 0);
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