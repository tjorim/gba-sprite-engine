//
// Created by Florian on 6/01/2019.
//

#include <libgba-sprite-engine/gba/tonc_types.h>
#include "EyeballMonster.h"

void EyeballMonster::tick(u16 keys) {

    getEyeballSprite()->setVelocity(-1, 0);
}
