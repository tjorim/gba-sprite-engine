//
// Created by tiele on 9/08/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>

#include "../game_scene/game_scene.h"
#include "book_scene.h"

#include "background/background_books.h"
#include "foreground/sprites/shared_book_scene.h"

BookScene::BookScene(const std::shared_ptr<GBAEngine> &engine, Character character) : Scene(engine), character(character) {}

std::vector<Background *> BookScene::backgrounds() {
    return {
            background_books.get()
    };
}

std::vector<Sprite *> BookScene::sprites() {
    std::vector<Sprite *> sprites;

    for (auto &book : books) {
        sprites.push_back(book->getSprite());
    }

    sprites.push_back(stair_case->getPlayerBookSprite());

    sprites.push_back(stair_case->getgetBooksBaseSprite());

    sprites.push_back(stair_case->getgetBooksBottomSprite());

    sprites.push_back(stair_case->getgetBooksMiddleSprite());

    sprites.push_back(stair_case->getgetBooksTopSprite());

    TextStream::instance().setText(std::string("Sprites ") + std::to_string(sprites.size()), 1, 0);

    return sprites;
}

void BookScene::load() {
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
}

void BookScene::tick(u16 keys) {
    a_last = a_now;
    if (keys & KEY_A) {
        a_now = true;
    } else {
        a_now = false;
    }
    if (a_now == true && a_last == false) {
        engine->setScene(new GameScene(engine, getCharacter()));
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
        stair_case->lower();
    }

    up_last = up_now;
    if (keys & KEY_UP) {
        up_now = true;
    } else {
        up_now = false;
    }
    if (up_now == true && up_last == false) {
        stair_case->higher();
    }

    TextStream::instance().setText(std::string("Book scene"), 0, 0);
}

Character BookScene::getCharacter() const {
    return character;
}

void BookScene::setCharacter(const Character &value) {
    character = value;
}

void BookScene::placeBooks() {
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::BLUE, 10, 0))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::GREEN, 40, 40))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::YELLOW, 70, 60))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::RED, 100, 0))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::GREEN, 130, 80))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::BLUE, 150, 60))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::RED, 180, 40))
    );
    books.push_back(
            std::unique_ptr<Book>(new Book(Colour::YELLOW, 200, 80))
    );
}