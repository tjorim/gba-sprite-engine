//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_THING_H
#define GBA_SPRITE_ENGINE_PROJECT_THING_H

#include <libgba-sprite-engine/sprites/sprite.h>

enum class thingType: char {BOMB = 1, CRATE = 2, FLOOR = 3, GUNPOWDER = 4, PLAYER = 5, PORTAL = 6, POWERUP = 7, WALL = 8};

class Thing {
private:
    thingType type;
    std::unique_ptr<Sprite> sprite;
    // De x-positie van the Thing
    int xCoGrid;
    // De y-positie van the Thing
    int yCoGrid;
public:
    Thing(int xCoGrid, int yCoGrid, thingType type) : xCoGrid(xCoGrid), yCoGrid(yCoGrid), type(type) {}

    /**
     * @brief What type is this thing?
     * @return thingType
     */
    thingType getType() { return type; }

    void setType(thingType type) {
        Thing::type = type;
    }

    Sprite* getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Thing::sprite = std::move(sprite);
    }

    virtual void moveTo(int xValue, int yValue) {
        setXCoGrid(xValue);
        setYCoGrid(yValue);
        sprite->moveTo(8*xValue, 8*yValue);
    }

    /**
     * Wat is de x-positie van this Thing?
     *
     * @return De x-positie van this Thing.
     */
    int getXCoGrid() const {return xCoGrid;}
    /**
     * Stel de x-positie van de speler in.
     *
     * @param xCoGrid De x-positie van de speler.
     */
    void setXCoGrid(int value)
    {
        xCoGrid = value;
    }

    /**
     * Wat is de y-positie van this Thing?
     *
     * @return De y-positie van this Thing.
     */
    int getYCoGrid() const {return yCoGrid;}
    /**
     * Stel de y-positie van de speler in.
     *
     * @param yCoGrid De y-positie van de speler.
     */
    void setYCoGrid(int value)
    {
        yCoGrid = value;
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_THING_H
