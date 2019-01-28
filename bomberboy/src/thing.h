//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_THING_H
#define GBA_SPRITE_ENGINE_PROJECT_THING_H

#include <libgba-sprite-engine/sprites/sprite.h>

class Thing {
private:
    std::unique_ptr<Sprite> sprite;
    // De x-positie van the Thing
    int xCo;
    // De y-positie van the Thing
    int yCo;
public:
    Thing(int xCo, int yCo) {}

    Sprite* getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Thing::sprite = std::move(sprite);
    }
    
    enum class thingType: char {BOMB = 1, CRATE = 2, FLOOR = 3, GUNPOWDER = 4, PLAYER = 5, PORTAL = 6, POWERUP = 7, WALL = 8};

    /**
     * @brief What type is this thing?
     * @return thingType
     */
    virtual thingType getType() = 0;

    virtual void move(int xValue, int yValue) {
        setXCo(xValue);
        setYCo(yValue);
        sprite->moveTo(8*xValue, 8*yValue);
    }

    /**
     * Wat is de x-positie van this Thing?
     *
     * @return De x-positie van this Thing.
     */
    int getXCo() const {return xCo;}
    /**
     * Stel de x-positie van de speler in.
     *
     * @param xCo De x-positie van de speler.
     */
    void setXCo(int value)
    {
        xCo = value;
    }

    /**
     * Wat is de y-positie van this Thing?
     *
     * @return De y-positie van this Thing.
     */
    int getYCo() const {return yCo;}
    /**
     * Stel de y-positie van de speler in.
     *
     * @param yCo De y-positie van de speler.
     */
    void setYCo(int value)
    {
        yCo = value;
    }
};


#endif //GBA_SPRITE_ENGINE_PROJECT_THING_H
