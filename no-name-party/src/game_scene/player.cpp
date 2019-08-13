//
// Created by tiele on 27/01/2019.
//

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

Player::Player(Character character, int xCo, int yCo) : character(character), xCo(xCo), yCo(yCo) {
    SpriteBuilder<Sprite> builder;

    switch (character) {
        case Character::LUIGI:
            sprite_down = std::move(builder.withData(luigi_downTiles,
                                                     sizeof(luigi_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(luigi_leftTiles,
                                                     sizeof(luigi_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(luigi_rightTiles,
                                                      sizeof(luigi_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withAnimated(4, 4)
                                             .withLocation(xCo, yCo)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(luigi_upTiles,
                                                   sizeof(luigi_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withAnimated(4, 4)
                                          .withLocation(xCo, yCo)
                                          .buildPtr());
            break;

        case Character::MARIO:
            break;

        case Character::PRINCESS_PEACH:
            sprite_down = std::move(builder.withData(princess_peach_downTiles,
                                                     sizeof(princess_peach_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(princess_peach_leftTiles,
                                                     sizeof(princess_peach_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withAnimated(4, 4)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(princess_peach_rightTiles,
                                                      sizeof(princess_peach_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withAnimated(4, 4)
                                             .withLocation(xCo, yCo)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(princess_peach_upTiles,
                                                   sizeof(princess_peach_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withAnimated(4, 4)
                                          .withLocation(xCo, yCo)
                                          .buildPtr());
            break;

        case Character::YOSHI:
            sprite_down = std::move(builder.withData(yoshi_downTiles,
                                                     sizeof(yoshi_downTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_left = std::move(builder.withData(yoshi_leftTiles,
                                                     sizeof(yoshi_leftTiles))
                                            .withSize(SIZE_32_32)
                                            .withLocation(xCo, yCo)
                                            .buildPtr());

            sprite_right = std::move(builder.withData(yoshi_rightTiles,
                                                      sizeof(yoshi_rightTiles))
                                             .withSize(SIZE_32_32)
                                             .withLocation(xCo, yCo)
                                             .buildPtr());

            sprite_up = std::move(builder.withData(yoshi_upTiles,
                                                   sizeof(yoshi_upTiles))
                                          .withSize(SIZE_32_32)
                                          .withLocation(xCo, yCo)
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

void Player::moveTo(int xValue, int yValue) {
    setXCo(xValue);
    setYCo(yValue);

    sprite_down->moveTo(xValue, yValue);
    sprite_left->moveTo(xValue, yValue);
    sprite_right->moveTo(xValue, yValue);
    sprite_up->moveTo(xValue, yValue);
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

int Player::getXCo() const {
    return xCo;
}

void Player::setXCo(int value) {
    xCo = value;
}

int Player::getScore() const {
    return score;
}

void Player::setPlayerNumber(int value) {
    playerNumber = value;
}

void Player::setCharacter(const Character &value) {
    character = value;
}

void Player::setDirection(const Direction &value) {
    direction = value;
}

int Player::getYCo() const {
    return yCo;
}

void Player::setYCo(int value) {
    yCo = value;
}

void Player::scoreHoger() {
    score++;
}

void Player::scoreLager() {
    score--;
}
