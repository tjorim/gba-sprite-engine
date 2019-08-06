//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
#define GBA_SPRITE_ENGINE_PROJECT_BALLOON_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../sprites/balloon_all.h"

// we only have four colours, so no need for ints!
enum class Colour : char {
    BLUE = 0, GREEN = 1, PINK = 2, YELLOW = 3
};

class Balloon {
private:
    std::unique_ptr<Sprite> sprite;

    Colour colour = Colour::BLUE;
    int xCo = GBA_SCREEN_WIDTH;
    int helium = 0, offset = 0;

public:
    Balloon(Colour colour, int xCo, int helium, int offset) : colour(colour), xCo(xCo), helium(helium), offset(offset) {
        SpriteBuilder<Sprite> spriteBuilder;
        setSprite(spriteBuilder
                          .withData(balloon_allTiles, sizeof(balloon_allTiles))
                          .withSize(SIZE_16_32)
                          .withAnimated(static_cast<int>(colour), 1, 0)
                          .withLocation(xCo, GBA_SCREEN_HEIGHT + offset)
                          .withVelocity(0, helium)
                          .buildPtr());
    }

    Sprite *getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Balloon::sprite = std::move(sprite);
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
