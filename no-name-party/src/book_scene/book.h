//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BOOK_H
#define GBA_SPRITE_ENGINE_PROJECT_BOOK_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../enums/colour.h"

#include "foreground/sprites/book_blue.h"
#include "foreground/sprites/book_green.h"
#include "foreground/sprites/book_red.h"
#include "foreground/sprites/book_yellow.h"

class Book {
private:
    std::unique_ptr <Sprite> sprite;

    int book_height[4] = {109, 85, 61, 37};

    int height = 0;
    int xCo = GBA_SCREEN_WIDTH / 2;

    // BLUE, GREEN, RED, YELLOW
    Colour colour = Colour::BLUE;

public:
    Book(Colour colour, int xCo, int height) : colour(colour), xCo(xCo), height(height) {
        SpriteBuilder <Sprite> builder;

        switch (colour) {
            case Colour::BLUE:
                setSprite(builder.withData(book_blueTiles, sizeof(book_blueTiles))
                                  .withSize(SIZE_16_16)
                                  .withLocation(xCo, height)
                                  .buildPtr());
                break;

            case Colour::GREEN:
                setSprite(builder.withData(book_greenTiles, sizeof(book_greenTiles))
                                  .withSize(SIZE_16_16)
                                  .withLocation(xCo, height)
                                  .buildPtr());
                break;

            case Colour::RED:
                setSprite(builder.withData(book_redTiles, sizeof(book_redTiles))
                                  .withSize(SIZE_16_16)
                                  .withLocation(xCo, height)
                                  .buildPtr());
                break;

            case Colour::YELLOW:
                setSprite(builder.withData(book_yellowTiles, sizeof(book_yellowTiles))
                                  .withSize(SIZE_16_16)
                                  .withLocation(xCo, height)
                                  .buildPtr());
                break;

            default:
                break;
        }

        updateHeight();
    }

    void moveToX(int xValue) {
        Book::xCo = xValue;
        updateHeight();
    }

    int getHeight() const {
        return height;
    }

    void setHeight(int height) {
        Book::height = height;
        updateHeight();
    }

    void updateHeight() {
        sprite->moveTo(xCo - 8, book_height[height]);
    }

    Colour getColour() const {
        return colour;
    }

    void setColour(const Colour &value) {
        Book::colour = value;
    }

    Sprite *getSprite() {
        return sprite.get();
    }

    void setSprite(std::unique_ptr <Sprite> sprite) {
        Book::sprite = std::move(sprite);
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BOOK_H
