//
// Created by Leander on 22/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PORTAL_H
#define GBA_SPRITE_ENGINE_PROJECT_PORTAL_H


#include <bits/unique_ptr.h>
#include <libgba-sprite-engine/sprites/sprite.h>

class Portal {
private:
    std::unique_ptr<Sprite> verticalPortal;
    std::unique_ptr<Sprite> horizontalPortal;
    bool orientation;
    int xCoordinaat, yCoordinaat;
    bool direction;

public:
    int getXCoordinaat() const;
    int getYCoordinaat() const;
    bool getDirection();

    Portal(std::unique_ptr<Sprite> sprite1, std::unique_ptr<Sprite> sprite2): verticalPortal(std::move(sprite1)), horizontalPortal(std::move(sprite2)){};

    Sprite* getVerticalSprite() { return verticalPortal.get(); }
    Sprite* getHorizontalSprite() { return horizontalPortal.get(); }

    bool getOrientation();
    void setPortal(bool orient, int Xcoor, int YCoor);

    void setXCoordinaat(int xCoordinaat);
    void setYCoordinaat(int yCoordinaat);
    void setDirection(bool dir);
};




#endif //GBA_SPRITE_ENGINE_PROJECT_PORTAL_H
