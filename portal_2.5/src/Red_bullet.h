#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>
#include <cmath>
class Red_bullet {
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


public:
    Red_bullet(std::unique_ptr<Sprite> sprite) : sprite(std::move(sprite)) {
    }
    void start();
    int getx();
    int gety();
    void tick();
    void setDestination(VECTOR vec);
    bool isOffScreen() { return sprite->isOffScreen(); }
};