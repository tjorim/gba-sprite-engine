//
// Created by tiele on 10/08/2019.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "stair_case.h"

#include "foreground/sprites/books_base.h"
#include "foreground/sprites/books_bottom.h"
#include "foreground/sprites/books_middle.h"
#include "foreground/sprites/books_top.h"

#include "foreground/sprites/luigi_book.h"
#include "foreground/sprites/mario_book.h"
#include "foreground/sprites/princess_peach_book.h"
#include "foreground/sprites/yoshi_book.h"

StairCase::StairCase(Character character) : character(character) {
    SpriteBuilder<Sprite> builder;

    switch (character) {
        case Character::LUIGI:
            player_book = std::move(builder.withData(luigi_bookTiles,
                                                     sizeof(luigi_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(centerX, centerY)
                                            .buildPtr());
            break;

        case Character::MARIO:
            player_book = std::move(builder.withData(mario_bookTiles,
                                                     sizeof(mario_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(centerX, centerY)
                                            .buildPtr());
            break;

        case Character::PRINCESS_PEACH:
            player_book = std::move(builder.withData(princess_peach_bookTiles,
                                                     sizeof(princess_peach_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(centerX, centerY)
                                            .buildPtr());
            break;

        case Character::YOSHI:
            player_book = std::move(builder.withData(yoshi_bookTiles,
                                                     sizeof(yoshi_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(centerX, centerY)
                                            .buildPtr());
            break;

        default:
            break;
    }
}

Sprite *StairCase::getPlayerSprite() {
    return player_book.get();
}

const std::unique_ptr<Sprite> &StairCase::getBooksBase() const {
    return books_base;
}

void StairCase::setBooksBase(const std::unique_ptr<Sprite> &booksBase) {
//    books_base = booksBase;
}

const std::unique_ptr<Sprite> &StairCase::getPlayerBook() const {
    return player_book;
}

void StairCase::setPlayerBook(const std::unique_ptr<Sprite> &playerBook) {
//    player_book = playerBook;
}

const std::unique_ptr<Sprite> &StairCase::getBooksBottom() const {
    return books_bottom;
}

void StairCase::setBooksBottom(const std::unique_ptr<Sprite> &booksBottom) {
//    books_bottom = booksBottom;
}

const std::unique_ptr<Sprite> &StairCase::getBooksMiddle() const {
    return books_middle;
}

void StairCase::setBooksMiddle(const std::unique_ptr<Sprite> &booksMiddle) {
//    books_middle = booksMiddle;
}

const std::unique_ptr<Sprite> &StairCase::getBooksTop() const {
    return books_top;
}

void StairCase::setBooksTop(const std::unique_ptr<Sprite> &booksTop) {
//    books_top = booksTop;
}

int StairCase::getHeight() const {
    return height;
}

void StairCase::setHeight(int height) {
    StairCase::height = height;
}

Character StairCase::getCharacter() const {
    return character;
}

void StairCase::setCharacter(Character character) {
    StairCase::character = character;
}
