//
// Created by Ruben on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYERCONTROLLER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYERCONTROLLER_H

#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "base_controller.h"
#include "../Models/Dude.h"

class PlayerController : public BaseController{

private:
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
public:
    void processKeys(u16 keys);

};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYERCONTROLLER_H
