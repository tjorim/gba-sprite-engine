//
// Created by tiele on 27/01/2019.
//

#include <math.h>

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "../../sprites/luigi_left.h"

Player::Player(int xCoGrid, int yCoGrid) : Thing(xCoGrid, yCoGrid, thingType::PLAYER) {
    setXCoSprite(8*xCoGrid);
    setYCoSprite(8*yCoGrid-8);
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(Luigi_leftTiles, sizeof(Luigi_leftTiles))
            .withSize(SIZE_32_32)
            .withLocation(120, 80) // xCoSprite, yCoSprite
            .buildPtr());
}

void Player::moveTo(int xValue, int yValue) {
    setXCoSprite(xValue);
    setYCoSprite(yValue);
    getSprite()->moveTo(xValue, yValue-8);
}

void Player::moveRelative(int xValue, int yValue) {
    int newX = xCoSprite+xValue;
    int newY = yCoSprite+yValue;
    moveTo(newX, newY);
}

/**
 * Beweeg 1 vakje naar boven.
 */
void Player::moveUp() {
    moveRelative(0,-1);
}

/**
 * Beweeg 1 vakje naar onder.
 */
void Player::moveDown() {
    moveRelative(0,1);
}

/**
 * Beweeg 1 vakje naar links.
 */
void Player::moveLeft() {
    moveRelative(-1,0);
}

/**
 * Beweeg 1 vakje naar rechts.
 */
void Player::moveRight() {
    moveRelative(1,0);
}

int Player::getXCoSprite() const {
    return xCoSprite;
}

void Player::setXCoSprite(int value) {
    Player::xCoSprite = value;
    setXCoGrid(round(double(value)/8));
}

int Player::getYCoSprite() const {
    return yCoSprite;
}

void Player::setYCoSprite(int value) {
    Player::yCoSprite = value;
    setYCoGrid(round(double(yCoSprite)/8));
}

int Player::getPlayerNumber() const
{
    return playerNumber;
}

bool Player::canShift() const
{
    return shift;
}

bool Player::canKick() const
{
    return kick;
}

Direction Player::getDirection() const
{
    return direction;
}

int Player::getAantalBommen() const
{
    return aantalBommen;
}

int Player::getMaxBommen()
{
    return maxBommen;
}

int Player::getHoeveelVuur() const
{
    return hoeveelVuur;
}

int Player::getMaxVuur() const
{
    return maxVuur;
}

bool Player::isDood()
{
    if (getLives() == 0) {
        return true;
    } else {
        return false;
    }
}

int Player::getLives() const
{
    return lives;
}

int Player::getMaxLevens()
{
    return maxLevens;
}

int Player::getSpeed() const
{
    return speed;
}

int Player::getMaxSnelheid()
{
    return maxSnelheid;
}

void Player::setPlayerNumber(int value)
{
    playerNumber = value;
}

void Player::setShift(bool value)
{
    shift = value;
}

void Player::setKick(bool value)
{
    kick = value;
}

void Player::setDirection(const Direction &value)
{
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
}

void Player::eenBomMinder()
{
    aantalBommen--;
}

void Player::eenBomMeer()
{
    if (getAantalBommen() < getMaxBommen()) {
        aantalBommen++;
    } else {
        aantalBommen = maxBommen;
    }
}

void Player::geefMaxBommen()
{
    aantalBommen = maxBommen;
}

void Player::setHoeveelVuur(int value)
{
    if (getHoeveelVuur() < getMaxVuur()) {
        hoeveelVuur = value;
    } else {
        hoeveelVuur = maxVuur;
    }
}

void Player::maakDood()
{
    lives = 0;
}

void Player::eenLevenMinder()
{
    lives--;
}

void Player::eenLevenMeer()
{
    if (getLives() < getMaxLevens())
    {
        lives++;
    }
    else
    {
        lives = maxLevens;
    }
}

void Player::geefMaxLevens()
{
    lives = maxLevens;
}

void Player::setSpeed(int value)
{
    if (getSpeed() < getMaxSnelheid()) {
        speed = value;
    } else {
        speed = maxSnelheid;
    }
}
