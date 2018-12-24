//
// Created by Leander on 21/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_WALLTILE_H
#define GBA_SPRITE_ENGINE_PROJECT_WALLTILE_H


#include <libgba-sprite-engine/sprites/sprite.h>

class WallTile {
private:
    std::unique_ptr<Sprite> tile;
    bool hasPortal = false;

public:
    WallTile(std::unique_ptr<Sprite> sprite) : tile(std::move(sprite)){};

    Sprite* getSprite() { return tile.get(); }

    u32 getXCoordinaat() const;
    u32 getYCoordinaat() const;
    u32 getXSnelheid() const;
    u32 getYSnelheid() const;
    bool getHasPortal();

    void setXCoodinaat(u32 xCoodinaat);
    void setYCoordinaat(u32 yCoordinaat);
    void setXSnelheid(u32 xSnelheid);
    void setYSnelheid(u32 ySnelheid);
    void setHasPortal(bool portal);
    void updateView();
};


#endif //GBA_SPRITE_ENGINE_PROJECT_WALLTILE_H
