//
// Created by tiele on 27/01/2019.
//

#include <math.h>

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "../sprites/car_all.h"

Player::Player(Character character) : character(character) {
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
                      .withData(car_allTiles, sizeof(car_allTiles))
                      .withSize(SIZE_32_32)
                      .withAnimated(getBeginFrame(), 4, 4)
                      .withLocation(GBA_SCREEN_WIDTH / 2 - 16, GBA_SCREEN_HEIGHT / 2 - 16)
                      .buildPtr());
}

/*
Sprite* getSprite() { return sprite.get(); }

void setSprite(std::unique_ptr<Sprite> sprite) {
    Player::sprite = std::move(sprite);
}
*/

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
    setDirection(Direction::BOVEN);
    moveRelative(0, -1);
}

/**
 * Beweeg 1 vakje naar onder.
 */
void Player::moveDown() {
    setDirection(Direction::ONDER);
    moveRelative(0, 1);
}

/**
 * Beweeg 1 vakje naar links.
 */
void Player::moveLeft() {
    setDirection(Direction::LINKS);
    moveRelative(-1, 0);
}

/**
 * Beweeg 1 vakje naar rechts.
 */
void Player::moveRight() {
    setDirection(Direction::RECHTS);
    moveRelative(1, 0);
}

int Player::getBeginFrame() {
    beginFrame = 16 * static_cast<int>(character) + 4 * static_cast<int>(direction);
    return beginFrame;
}

void Player::updateBeginFrame() {
    beginFrame = 16 * static_cast<int>(character) + 4 * static_cast<int>(direction);
    sprite->setBeginFrame(beginFrame);
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
        case Direction::ONDER:
            // pas sprite aan
            break;
        case Direction::BOVEN:
            // pas sprite aan
            break;
        case Direction::LINKS:
            // pas sprite aan
            break;
        case Direction::RECHTS:
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
