//
// Created by Leander on 25/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BUTTON_H
#define GBA_SPRITE_ENGINE_PROJECT_BUTTON_H


#include <libgba-sprite-engine/sprites/sprite.h>

class Button {
private:
    std::unique_ptr<Sprite> button;


public:
    Button(std::unique_ptr<Sprite> sprite) : button(std::move(sprite)){};
    Sprite* getSprite() { return button.get(); }


};
#endif //GBA_SPRITE_ENGINE_PROJECT_BUTTON_H
