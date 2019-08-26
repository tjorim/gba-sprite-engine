//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>

#include "../game_scene/game_scene.h"
#include "book_scene.h"

#include "background/background_books.h"
#include "foreground/sprites/shared_book_scene.h"

BookScene::BookScene(const std::shared_ptr <GBAEngine> &engine, std::shared_ptr <Player> &player) : Scene(engine),
                                                                                       player(player) {}

std::vector<Background *> BookScene::backgrounds() {
    return {
            background_books.get()
    };
}

std::vector<Sprite *> BookScene::sprites() {
    std::vector < Sprite * > sprites;

    sprites.push_back(stair_case->getPlayerBookSprite());

    sprites.push_back(stair_case->getgetBooksBaseSprite());

    sprites.push_back(stair_case->getgetBooksBottomSprite());

    sprites.push_back(stair_case->getgetBooksMiddleSprite());

    sprites.push_back(stair_case->getgetBooksTopSprite());

    for (auto &book : books) {
        sprites.push_back(book->getSprite());
    }

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void BookScene::load() {
    TextStream::instance().clear();

    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(
            new BackgroundPaletteManager(background_booksPal, sizeof(background_booksPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(
            new ForegroundPaletteManager(shared_book_scenePal, sizeof(shared_book_scenePal)));

    background_books = std::unique_ptr<Background>(
            new Background(1, background_booksTiles, sizeof(background_booksTiles),
                           background_booksMap, sizeof(background_booksMap)));
    background_books->useMapScreenBlock(16);

    placeBooks();

    stair_case = std::unique_ptr<StairCase>(new StairCase(getCharacter()));

    updateXCo();
}

void BookScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        engine->setScene(new GameScene(engine, player));
    }

    b_last = b_now;
    if (keys & KEY_B) {
        b_now = true;
    } else {
        b_now = false;
    }
    if (b_now == true && b_last == false) {
        //engine->setScene(new StartScene(engine));
        //engine->dequeueAllSounds();
        //engine->enqueueMusic(Title_Screen_wav, sizeof(Title_Screen_wav));
    }

    down_last = down_now;
    if (keys & KEY_DOWN) {
        down_now = true;
    } else {
        down_now = false;
    }
    if (down_now == true && down_last == false) {
        lower();
    }

    up_last = up_now;
    if (keys & KEY_UP) {
        up_now = true;
    } else {
        up_now = false;
    }
    if (up_now == true && up_last == false) {
        higher();
    }

    left_last = left_now;
    if (keys & KEY_LEFT) {
        left_now = true;
    } else {
        left_now = false;
    }
    if (left_now == true && left_last == false) {
        goLeft();
    }

    right_last = right_now;
    if (keys & KEY_RIGHT) {
        right_now = true;
    } else {
        right_now = false;
    }
    if (right_now == true && right_last == false) {
        goRight();
    }

    TextStream::instance().setText(std::string("Book scene"), 0, 0);
}

void BookScene::higher() {
    if (height < 3) {
        height++;
        updateHeight();
    }
}

void BookScene::lower() {
    if (height > 0) {
        height--;
        updateHeight();
    }
}

void BookScene::updateHeight() {
    stair_case->setHeight(height);
}

void BookScene::goLeft() {
    if (xCo > 112) {
        xCo -= 16;
        updateXCo();
    }
}

void BookScene::goRight() {
    if (xCo < 128) {
        xCo += 16;
        updateXCo();
    }
}

void BookScene::updateXCo() {
    stair_case->moveToX(xCo);
}

Character BookScene::getCharacter() const {
    return character;
}

void BookScene::setCharacter(const Character &value) {
    character = value;
}

void BookScene::placeBooks() {
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::BLUE, 112, 3))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::GREEN, 112, 2))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::YELLOW, 112, 1))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::RED, 112, 0))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::GREEN, 128, 3))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::BLUE, 128, 2))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::RED, 128, 1))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::YELLOW, 128, 0))
    );
}