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
    sprites.push_back(player2->getSprite());

    for (auto &rows: board) {
        for (auto &elem: rows) {
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

    player1 = std::unique_ptr<Player>(new Player(1, 1));
    player1->setPlayerNumber(1);
    player2 = std::unique_ptr<Player>(new Player(BOARD_WIDTH - 2, BOARD_HEIGHT - 2));
    player2->setPlayerNumber(2);

    for (int i = 0; i < BOARD_WIDTH; i++) { // board.size(), Iterating over rows
        for (int j = 0; j < BOARD_HEIGHT; j++) { // board[i].size()
            if(i == 0 || i == BOARD_WIDTH-1 || j == 0 || j == BOARD_HEIGHT-1 || (i % 2 == 0 && j % 2 == 0)) {
                board[i][j] = new Wall(i, j);
            } else if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1) ||
                       (i == BOARD_WIDTH - 2 && j == BOARD_HEIGHT - 2) ||
                       (i == BOARD_WIDTH - 2 && j == BOARD_HEIGHT - 3) ||
                       (i == BOARD_WIDTH - 3 && j == BOARD_HEIGHT - 2)) {
                board[i][j] = new Floor(i, j);
            } else if ((i + j + level) % 7 == 0) {
                board[i][j] = new PowerUp(i, j);
            } else if ((i * j + level) % 5 == 0) {
                board[i][j] = new Gunpowder(i, j);
            } else if ((i + j + level) % 2 == 0) {
                board[i][j] = new Crate(i, j);
            } else {
                board[i][j] = new Floor(i, j);
            }
        }
    }

}

void GameScene::tick(u16 keys) {
    TextStream::instance().setText(std::string("Game scene"), 5, 1);

    updateBombs();

    if (player1->isDood() || player2->isDood()) {
        engine->setScene(new EndScene(engine));
    }

    if (keys & KEY_FIRE) {
        dropBomb();
    } else if (keys & KEY_UP) {
        movePlayer(0, -1);
    } else if (keys & KEY_DOWN) {
        movePlayer(0, 1);
    } else if (keys & KEY_LEFT) {
        movePlayer(-1, 0);
    } else if (keys & KEY_RIGHT) {
        movePlayer(1, 0);
    }
}

thingType GameScene::getThingType(int xValue, int yValue) {
    thingType type = board[xValue][yValue]->getType();
    TextStream::instance().setText(std::string("Type: ") + std::to_string(
        static_cast<std::underlying_type<thingType>::type>(type)
        ), 13, 1);
    return type;
}

void GameScene::dropBomb() {
    if(player1->getAantalBommen() > 0) {
        int bombX = player1->getXCoGrid();
        int bombY = player1->getYCoGrid();
        thingType thingUnderPlayerType = getThingType(bombX, bombY);

        if(thingUnderPlayerType == thingType::FLOOR || thingUnderPlayerType == thingType::GUNPOWDER) {
            bombs.push_back(std::unique_ptr<Bomb>(new Bomb(bombX, bombY)));
            engine.get()->updateSpritesInScene();
            TextStream::instance().setText(std::string("Boms ") + std::to_string(bombs.size()), 10, 1);
            player1->eenBomMinder();
        }
    }
}

void GameScene::updateBombs() {
    bool spritesChanged = false;

    for (auto bomb = bombs.begin(); bomb != bombs.end();) {
        if ((*bomb)->tick()) {
            explodeBomb(bomb->get());
            bomb = bombs.erase(bomb);
            player1->eenBomMeer();
            spritesChanged = true;
        } else {
            ++bomb;
        }
    }

    if (spritesChanged) {
        engine.get()->updateSpritesInScene();
    }
}

void GameScene::explodeBomb(Bomb *bomb) {
    static const int directions[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    applyExplosionToTile(bomb->getXCoGrid(), bomb->getYCoGrid());

    for (auto &direction : directions) {
        for (int distance = 1; distance <= player1->getHoeveelVuur(); distance++) {
            int xValue = bomb->getXCoGrid() + direction[0] * distance;
            int yValue = bomb->getYCoGrid() + direction[1] * distance;

            if (!applyExplosionToTile(xValue, yValue)) {
                break;
            }
        }
    }
}

bool GameScene::applyExplosionToTile(int xValue, int yValue) {
    if (!isInsideBoard(xValue, yValue)) {
        return false;
    }

    if (player1->getXCoGrid() == xValue && player1->getYCoGrid() == yValue) {
        player1->maakDood();
    }
    if (player2->getXCoGrid() == xValue && player2->getYCoGrid() == yValue) {
        player2->maakDood();
    }

    thingType type = board[xValue][yValue]->getType();

    if (type == thingType::WALL) {
        return false;
    }

    if (type == thingType::CRATE || type == thingType::POWERUP || type == thingType::GUNPOWDER) {
        delete board[xValue][yValue];
        board[xValue][yValue] = new Floor(xValue, yValue);
        return type == thingType::GUNPOWDER;
    }

    return true;
}

bool GameScene::isInsideBoard(int xValue, int yValue) {
    return xValue >= 0 && xValue < BOARD_WIDTH && yValue >= 0 && yValue < BOARD_HEIGHT;
}

bool GameScene::isWalkable(int xValue, int yValue) {
    if (!isInsideBoard(xValue, yValue)) {
        return false;
    }

    thingType type = board[xValue][yValue]->getType();
    return type == thingType::FLOOR || type == thingType::GUNPOWDER || type == thingType::POWERUP;
}

void GameScene::movePlayer(int xValue, int yValue) {
    int targetX = player1->getXCoGrid() + xValue;
    int targetY = player1->getYCoGrid() + yValue;

    if (player2->getXCoGrid() == targetX && player2->getYCoGrid() == targetY) {
        return;
    }

    if (isWalkable(targetX, targetY)) {
        player1->moveRelative(xValue, yValue);
    }
}
