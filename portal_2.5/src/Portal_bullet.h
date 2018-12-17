#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/gba/tonc_math.h>
#include <cmath>
#include <libgba-sprite-engine/sprites/affine_sprite.h>

class Portal_bullet {
private:
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
    bool isMoving = false;


public:

    void start(bool flip, int xLoc, int yLoc);
    int getx();
    int gety();
    bool getIsMoving();
    void setIsMoving(bool move);
    void tick();
    void setDestination(int pc, int X, int Y, int With);
};