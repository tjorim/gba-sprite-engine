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
                                            .withLocation(xCo - 16, GBA_SCREEN_HEIGHT - 64)
                                            .buildPtr());
            break;

        case Character::MARIO:
            player_book = std::move(builder.withData(mario_bookTiles,
                                                     sizeof(mario_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(xCo - 16, GBA_SCREEN_HEIGHT - 64)
                                            .buildPtr());
            break;

        case Character::PRINCESS_PEACH:
            player_book = std::move(builder.withData(princess_peach_bookTiles,
                                                     sizeof(princess_peach_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(xCo - 16, GBA_SCREEN_HEIGHT - 64)
                                            .buildPtr());
            break;

        case Character::YOSHI:
            player_book = std::move(builder.withData(yoshi_bookTiles,
                                                     sizeof(yoshi_bookTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(xCo - 16, GBA_SCREEN_HEIGHT - 64)
                                            .buildPtr());
            break;

        default:
            break;
    }

    books_base = std::move(builder.withData(books_baseTiles,
                                                sizeof(books_baseTiles))
                                    .withSize(SIZE_32_16)
                                    .withLocation(xCo - 16, GBA_SCREEN_HEIGHT / 2 + 32)
                                    .buildPtr());

    books_bottom = std::move(builder.withData(books_bottomTiles,
                                                sizeof(books_bottomTiles))
                                    .withSize(SIZE_32_32)
                                    .withLocation(xCo - 16, GBA_SCREEN_HEIGHT / 2)
                                    .buildPtr());

    books_middle = std::move(builder.withData(books_middleTiles,
                                                sizeof(books_middleTiles))
                                    .withSize(SIZE_16_32)
                                    .withLocation(xCo - 8, GBA_SCREEN_HEIGHT / 2 - 32)
                                    .buildPtr());

    books_top = std::move(builder.withData(books_topTiles,
                                                sizeof(books_topTiles))
                                    .withSize(SIZE_32_32)
                                    .withLocation(xCo - 16, GBA_SCREEN_HEIGHT / 2 - 64)
                                    .buildPtr());
}

void moveTo(int xValue, int yValue);

void higher();

void lower();

int StairCase::getHeight() const {
    return height;
}

void StairCase::setHeight(int height) {
    StairCase::height = height;
        //cloud_left->moveTo(cloud_left->getX(), yCo);
        //cloud_right->moveTo(cloud_right->getX(), yCo);
}

Character StairCase::getCharacter() const {
    return character;
}

void StairCase::setCharacter(const Character &value) {
    StairCase::character = character;
}

Sprite *StairCase::getPlayerBookSprite() {
    return player_book.get();
}

Sprite *StairCase::getgetBooksBaseSprite() {
    return books_base.get();
}

Sprite *StairCase::getgetBooksBottomSprite() {
    return books_bottom.get();
}

Sprite *StairCase::getgetBooksMiddleSprite() {
    return books_middle.get();
}

Sprite *StairCase::getgetBooksTopSprite() {
    return books_top.get();
}