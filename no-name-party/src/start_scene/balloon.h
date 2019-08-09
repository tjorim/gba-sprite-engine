//
// Created by tiele on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
#define GBA_SPRITE_ENGINE_PROJECT_BALLOON_H

#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>

#include "../enums/colour.h"

#include "foreground/sprites/balloon_blue.h"
#include "foreground/sprites/balloon_green.h"
#include "foreground/sprites/balloon_pink.h"
#include "foreground/sprites/balloon_yellow.h"

class Balloon {
private:
    std::unique_ptr<Sprite> sprite;

    Colour colour = Colour::BLUE;
    int xCo = GBA_SCREEN_WIDTH;
    int helium = 0, offset = 0;

public:
    Balloon(Colour colour, int xCo, int helium, int offset) : colour(colour), xCo(xCo), helium(helium), offset(offset) {
        SpriteBuilder<Sprite> builder;

        switch (colour) {
            case Colour::BLUE:
                setSprite(builder.withData(balloon_blueTiles, sizeof(balloon_blueTiles))
                                  .withSize(SIZE_16_32)
                                  .withLocation(xCo, GBA_SCREEN_HEIGHT + offset)
                                  .withVelocity(0, helium)
                                  .buildPtr());
                break;

            case Colour::GREEN:
                setSprite(builder.withData(balloon_greenTiles, sizeof(balloon_greenTiles))
                                  .withSize(SIZE_16_32)
                                  .withLocation(xCo, GBA_SCREEN_HEIGHT + offset)
                                  .withVelocity(0, helium)
                                  .buildPtr());
                break;

            case Colour::PINK:
                setSprite(builder.withData(balloon_pinkTiles, sizeof(balloon_pinkTiles))
                                  .withSize(SIZE_16_32)
                                  .withLocation(xCo, GBA_SCREEN_HEIGHT + offset)
                                  .withVelocity(0, helium)
                                  .buildPtr());
                break;

            case Colour::YELLOW:
                setSprite(builder.withData(balloon_yellowTiles, sizeof(balloon_yellowTiles))
                                  .withSize(SIZE_16_32)
                                  .withLocation(xCo, GBA_SCREEN_HEIGHT + offset)
                                  .withVelocity(0, helium)
                                  .buildPtr());
                break;

            default:
                break;
        }
    }

    Sprite *getSprite() { return sprite.get(); }

    void setSprite(std::unique_ptr<Sprite> sprite) {
        Balloon::sprite = std::move(sprite);
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_BALLOON_H
