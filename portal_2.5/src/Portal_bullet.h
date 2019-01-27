
#ifndef GBA_SPRITE_ENGINE_PROJECT_PORTAL_BULLET_H
#define GBA_SPRITE_ENGINE_PROJECT_PORTAL_BULLET_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>
#include <cmath>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Portal_bullet {
private:
    std::unique_ptr<Sprite> bullet;
    VECTOR dest;
    double speed = 0;
    double time;
    double distance;
    double directionX;
    double directionY;
    double newX;
    double newY;
    bool flip_visier;
    bool isMoving = false;


public:
    Portal_bullet(std::unique_ptr<Sprite> sprite) : bullet(std::move(sprite)){};

    void start(bool flip, int xLoc, int yLoc);
    int getx();
    int gety();
    bool getIsMoving();
    void setIsMoving(bool move);
    void tick();
    void setDestination(int pc, int X, int Y, int With);
    void setx(int x);
    void sety(int y);

    Sprite* getSprite() { return bullet.get(); }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_CHELL_H