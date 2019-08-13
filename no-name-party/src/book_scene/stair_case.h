//
// Created by tiele on 10/08/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_STAIR_CASE_H
#define GBA_SPRITE_ENGINE_PROJECT_STAIR_CASE_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>

#include "../enums/character.h"

class StairCase {
private:
    std::unique_ptr<Sprite> books_base, player_book;
    std::unique_ptr<Sprite> books_bottom, books_middle, books_top; //books_middle_2

    int height = 0;
    int centerX = GBA_SCREEN_WIDTH / 2 - 16, centerY = GBA_SCREEN_HEIGHT / 2 - 16;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;
public:
    StairCase(Character character);

    Sprite *getPlayerSprite();

    const std::unique_ptr<Sprite> &getBooksBase() const;

    void setBooksBase(const std::unique_ptr<Sprite> &booksBase);

    const std::unique_ptr<Sprite> &getPlayerBook() const;

    void setPlayerBook(const std::unique_ptr<Sprite> &playerBook);

    const std::unique_ptr<Sprite> &getBooksBottom() const;

    void setBooksBottom(const std::unique_ptr<Sprite> &booksBottom);

    const std::unique_ptr<Sprite> &getBooksMiddle() const;

    void setBooksMiddle(const std::unique_ptr<Sprite> &booksMiddle);

    const std::unique_ptr<Sprite> &getBooksTop() const;

    void setBooksTop(const std::unique_ptr<Sprite> &booksTop);

    int getHeight() const;

    void setHeight(int height);

    Character getCharacter() const;

    void setCharacter(Character character);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_STAIR_CASE_H
