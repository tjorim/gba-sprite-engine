//
// Created by Ruben on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_DUDE_H
#define GBA_SPRITE_ENGINE_PROJECT_DUDE_H

#include "base_model.h"
#include "../lib/RCoord.h"
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text_stream.h>

class Dude : public BaseModel {
private:
    RCoord _pos;

public:
    Dude();
    Dude(RCoord pos);
    Dude(int x, int y);
    void updateSprite() override;
    void move(RCoord pos);
    void move(int x, int y);
    void moveTo(RCoord pos);
    void moveTo(int x, int y);
    int getX() {return _pos.GetX();}
    int getY() {return _pos.GetY();}
    RCoord getPos() { return _pos;}


};


#endif //GBA_SPRITE_ENGINE_PROJECT_DUDE_H
