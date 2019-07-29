//
// Created by 11401165 on 26/11/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_bios.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "balletje.h"



// in 1/256 pixels
#define SPEED 50

u32 length(VECTOR a) {
    return Sqrt(a.x * a.x + a.y * a.y);
}


/*void Balletje::setDestination(VECTOR vec) {
    this->dest = vec;
}*/

// TODO https://gamedev.stackexchange.com/questions/23447/moving-from-ax-y-to-bx1-y1-with-constant-speed
void Balletje::tick() {
    auto pos = sprite->getPos();
    auto width = sprite->getWidth();
    auto height = sprite->getHeight();

    if(pos.x <= 0 || pos.x >= (GBA_SCREEN_WIDTH - width)) {
        dx = -dx;
    }
    if(pos.y <= 0 || pos.y >= (GBA_SCREEN_HEIGHT - height) ) {
        dy = -dy;
    }

    vel.x = number*dx;
    vel.y = dy;

    TextStream::instance().setText(std::string("pos/dest: (") + std::to_string(pos.x) + std::string(",") + std::to_string(pos.y) + std::string(") (") + std::to_string(dest.x) + std::string(",") + std::to_string(dest.y) + std::string(")"), 16, 1);

    sprite->setVelocity(vel.x, vel.y);

}
