//
// Created by Leander on 22/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_VISIER_H
#define GBA_SPRITE_ENGINE_PROJECT_VISIER_H


#include <libgba-sprite-engine/sprites/sprite.h>
#include <bits/unique_ptr.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Visier {
private:
    std::unique_ptr<AffineSprite> visier;
    int visierRotation = 0;
    bool flipVisier = false;


public:
    Visier(std::unique_ptr<AffineSprite> sprite): visier(std::move(sprite)){};

    Sprite* getSprite() { return visier.get(); }

    u32 getXCoordinaat() const;
    u32 getYCoordinaat() const;
    int getXSnelheid() const;
    int getYSnelheid() const;
    int getPc();
    bool getFlipVisier();

    void setXCoodinaat(u32 xCoodinaat);
    void setYCoordinaat(u32 yCoordinaat);
    void setXSnelheid(int xSnelheid);
    void setYSnelheid(int ySnelheid);
    void setLocation(int x, int y);

    void rotate(bool richting);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_VISIER_H
