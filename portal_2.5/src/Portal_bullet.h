#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>
#include <cmath>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Portal_bullet {
private:
    std::unique_ptr<Sprite> sprite;
    VECTOR dest;
    double speed = 0;
    double time;
    double distance;
    double directionX;
    double directionY;
    int teller;
    double newX;
    double newY;
    bool flip_visier;


public:
    Portal_bullet(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {
    }
    void start(bool flip);
    int getx();
    int gety();
    void tick();
    void setDestination(int pc, int X, int Y, int With);
    bool isOffScreen() { return sprite->isOffScreen(); }
};