//
// Created by tiele on 27/01/2019.
//

#include <math.h>

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"

#include "foreground/sprites/luigi_down.h"
#include "foreground/sprites/luigi_left.h"
#include "foreground/sprites/luigi_right.h"
#include "foreground/sprites/luigi_up.h"

#include "foreground/sprites/princess_peach_down.h"
#include "foreground/sprites/princess_peach_left.h"
#include "foreground/sprites/princess_peach_right.h"
#include "foreground/sprites/princess_peach_up.h"

#include "foreground/sprites/yoshi_down.h"
#include "foreground/sprites/yoshi_left.h"
#include "foreground/sprites/yoshi_right.h"
#include "foreground/sprites/yoshi_up.h"

Player::Player(Character character) : character(character) {
    SpriteBuilder<Sprite> builder;

    switch (character) {
        case Character::LUIGI:
            sprite_down = std::move(builder.withData(luigi_downTiles,
                                                     sizeof(luigi_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(luigi_leftTiles,
                                                     sizeof(luigi_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(luigi_rightTiles,
                                                      sizeof(luigi_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withAnimated(4, 4)
                                             .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(luigi_upTiles,
                                                   sizeof(luigi_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withAnimated(4, 4)
                                          .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                          .buildPtr());
            break;

        case Character::MARIO:
            break;

        case Character::PRINCESS_PEACH:
            sprite_down = std::move(builder.withData(princess_peach_downTiles,
                                                     sizeof(princess_peach_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(princess_peach_leftTiles,
                                                     sizeof(princess_peach_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(princess_peach_rightTiles,
                                                      sizeof(princess_peach_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withAnimated(4, 4)
                                             .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(princess_peach_upTiles,
                                                   sizeof(princess_peach_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withAnimated(4, 4)
                                          .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                          .buildPtr());
            break;

        case Character::YOSHI:
            sprite_down = std::move(builder.withData(yoshi_downTiles,
                                                     sizeof(yoshi_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(yoshi_leftTiles,
                                                     sizeof(yoshi_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(yoshi_rightTiles,
                                                      sizeof(yoshi_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(yoshi_upTiles,
                                                   sizeof(yoshi_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                                          .buildPtr());
            break;

        default:
            break;
    }
}

Sprite *Player::getSprite() {
    switch (direction) {
        case Direction::DOWN:
            return sprite_down.get();
            break;

        case Direction::LEFT:
            return sprite_left.get();
            break;

        case Direction::RIGHT:
            return sprite_right.get();
            break;

        case Direction::UP:
            return sprite_up.get();
            break;

        default:
            break;
    }
}

/*void setSprite(std::unique_ptr<Sprite> sprite) {
    Player::sprite = std::move(sprite);
}*/

void Player::moveTo(int xValue, int yValue) {
    setXCo(xValue);
    setYCo(yValue);
    getSprite()->moveTo(xValue, yValue);
    //sprite->moveTo(8*xValue, 8*yValue);
}

void Player::moveRelative(int xValue, int yValue) {
    int newX = xCo + xValue;
    int newY = yCo + yValue;
    moveTo(newX, newY);
}

/**
 * Beweeg 1 vakje naar boven.
 */
void Player::moveUp() {
    setDirection(Direction::UP);
    moveRelative(0, -1);
}

/**
 * Beweeg 1 vakje naar onder.
 */
void Player::moveDown() {
    setDirection(Direction::DOWN);
    moveRelative(0, 1);
}

/**
 * Beweeg 1 vakje naar links.
 */
void Player::moveLeft() {
    setDirection(Direction::LEFT);
    moveRelative(-1, 0);
}

/**
 * Beweeg 1 vakje naar rechts.
 */
void Player::moveRight() {
    setDirection(Direction::RIGHT);
    moveRelative(1, 0);
}

int Player::getBeginFrame() {
    beginFrame = 16 * static_cast<int>(character) + 4 * static_cast<int>(direction);
    return beginFrame;
}

void Player::updateBeginFrame() {
    beginFrame = 16 * static_cast<int>(character) + 4 * static_cast<int>(direction);
    //sprite->setBeginFrame(beginFrame);
}

int Player::getXCo() const {
    return xCo;
}

void Player::setXCo(int value) {
    Player::xCo = value;
}

int Player::getYCo() const {
    return yCo;
}

void Player::setYCo(int value) {
    Player::yCo = value;
}

int Player::getPlayerNumber() const {
    return playerNumber;
}

Character Player::getCharacter() const {
    return character;
}

Direction Player::getDirection() const {
    return direction;
}

void Player::setPlayerNumber(int value) {
    playerNumber = value;
}

void Player::setCharacter(const Character &value) {
    switch (value) {
        case Character::LUIGI:
            // pas sprite aan
            break;
        case Character::PRINCESS_PEACH:
            // pas sprite aan
            break;
        default:
            return;
    }
    character = value;

    updateBeginFrame();
}

void Player::setDirection(const Direction &value) {
    switch (value) {
        case Direction::DOWN:
            // pas sprite aan
            break;
        case Direction::LEFT:
            // pas sprite aan
            break;
        case Direction::RIGHT:
            // pas sprite aan
            break;
        case Direction::UP:
            // pas sprite aan
            break;
        default:
            return;
    }
    direction = value;

    updateBeginFrame();
}

void Player::scoreHoger() {
    score++;
}

void Player::scoreLager() {
    score--;
}

int Player::getScore() const {
    return 0;
}
