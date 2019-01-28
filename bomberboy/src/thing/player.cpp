//
// Created by tiele on 27/01/2019.
//

#include <math.h>

#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "player.h"
#include "../../sprites/blauw_dood.h"

Player::Player(int xCoGrid, int yCoGrid) : Thing(xCoGrid, yCoGrid, thingType::PLAYER) {
    setXCoSprite(8*xCoGrid);
    setYCoSprite(8*yCoGrid-8);
    SpriteBuilder<Sprite> spriteBuilder;
    setSprite(spriteBuilder
            .withData(blauw_doodTiles, sizeof(blauw_doodTiles))
            .withSize(SIZE_8_16)
            .withLocation(xCoSprite, yCoSprite)
            .buildPtr());
}

void Player::move(int xValue, int yValue) {
    setXCoSprite(xValue);
    setYCoSprite(yValue);
    getSprite()->moveTo(xValue, yValue-8);
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

int Player::getAantalBommen() const
{
    return aantalBommen;
}

int Player::getHoeveelVuur() const
{
    return hoeveelVuur;
}

int Player::getMaxVuur() const
{
    return maxVuur;
}

int Player::getLives() const
{
    return lives;
}

int Player::getSpeed() const
{
    return speed;
}

bool Player::canShift() const
{
    return shift;
}

bool Player::canKick() const
{
    return kick;
}

int Player::getMaxSnelheid()
{
    return maxSnelheid;
}

int Player::getMaxLevens()
{
    return maxLevens;
}

int Player::getMaxBommen()
{
    return maxBommen;
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

void Player::setHoeveelVuur(int value)
{
    if (getHoeveelVuur() < getMaxVuur()) {
        hoeveelVuur = value;
    } else {
        hoeveelVuur = maxVuur;
    }
}

void Player::setSpeed(int value)
{
    if (getSpeed() < getMaxSnelheid()) {
        speed = value;
    } else {
        speed = maxSnelheid;
    }
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

Direction Player::getDirection() const
{
    return direction;
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
