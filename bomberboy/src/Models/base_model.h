#ifndef BASE_MODEL_H
#define BASE_MODEL_H

#include <libgba-sprite-engine/sprites/sprite.h>

class BaseModel {

private:
    Sprite* _sprite;


public:
    void setView(Sprite* sprite) {_sprite = sprite;}
    Sprite* getView() {
        return _sprite;
    }
    virtual void updateSprite() = 0;

};

#endif //BASE_MODEL_H