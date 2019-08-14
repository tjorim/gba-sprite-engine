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
    std::unique_ptr<Sprite> player_book, books_base;
    std::unique_ptr<Sprite> books_bottom, books_middle, books_top; //books_middle_2

    int player_book_height[4] = {96, 72, 48, 24};
    int books_base_height[4] = {128, GBA_SCREEN_HEIGHT, GBA_SCREEN_HEIGHT, GBA_SCREEN_HEIGHT};
    int books_bottom_height[4] = {GBA_SCREEN_HEIGHT, 112, 112, 112};
    int books_middle_height[4] = {GBA_SCREEN_HEIGHT, GBA_SCREEN_HEIGHT, 89, 80};
    int books_top_height[4] = {GBA_SCREEN_HEIGHT, 104, 80, 56};

    int height = 0;
    int xCo = GBA_SCREEN_WIDTH / 2;

    // LUIGI, MARIO, PRINCESS_PEACH, YOSHI
    Character character = Character::LUIGI;
public:
    StairCase(Character character);

    void moveTo(int xValue, int yValue);

    void higher();

    void lower();

    int getHeight() const;

    void setHeight(int height);

    void updateHeight();

    Character getCharacter() const;

    void setCharacter(const Character &value);

    Sprite *getPlayerBookSprite();

    Sprite *getgetBooksBaseSprite();

    Sprite *getgetBooksBottomSprite();

    Sprite *getgetBooksMiddleSprite();

    Sprite *getgetBooksTopSprite();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_STAIR_CASE_H
