//
// Created by 11401165 on 30/11/2018.
//

#include "Ball.h"
//
// Created by 11401165 on 26/11/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_bios.h>
#include <libgba-sprite-engine/gba_engine.h>

void Ball::tick() {
    auto pos = sprite->getPos();
    auto width = sprite->getWidth();
    auto height = sprite->getHeight();

    if(pos.x <= 0 || pos.x >= (GBA_SCREEN_WIDTH - width)) {
        dx = -dx;
    }
    if(pos.y <= (60 - 25*number) ) {
        dy = 1;
    }
    if( pos.y >= (GBA_SCREEN_HEIGHT - height) ) {
        dy = -1;
    }

    vel.x = dx;
    vel.y = dy;

    sprite->setVelocity(vel.x, vel.y);

}

/*u32 length(VECTOR a) {
    return Sqrt(a.x * a.x + a.y * a.y);
}*/
