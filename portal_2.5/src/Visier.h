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
    int getPc();
    bool getFlipVisier();
    void setXSnelheid(int xSnelheid);
    void setYSnelheid(int ySnelheid);
    void setLocation(int x, int y);

    void rotate(bool richting);
};

#endif //GBA_SPRITE_ENGINE_PROJECT_VISIER_H
