//
// Created by mathi on 27/01/2019.
//

#include "end_scene.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "background.h"
#include "LuigiTiles.h"
#include "sharedPal.h"
#include "Luigi.h"

#define bottomHeightFor32 45
#define bottomHeightFor16 29

std::vector<Background *> end_scene::backgrounds() {
    return {bg.get()};
}

void end_scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(spritesPal, sizeof(spritesPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    SpriteBuilder<AffineSprite> affineBuilder;

    luigiSprite = affineBuilder
            .withData(luigi_animationTiles, sizeof(luigi_animationTiles))
            .withSize(SIZE_16_32)
            .withLocation(10, GBA_SCREEN_HEIGHT - bottomHeightFor32)
            .withAnimated(5, 5)
            .buildPtr();

    luigi = std::unique_ptr<Luigi>{new Luigi(std::move(luigiSprite))};
    luigi->getLuigiSprite()->stopAnimating();
    luigi->setCurrentLvl(2);
}
std::vector<Sprite *> end_scene::sprites() {

    std::vector<Sprite *> sprites;
    sprites.push_back(luigi->getLuigiSprite().get());
}

void end_scene::tick(u16 keys) {
    if(!luigi->isDead() ) {
        TextStream::instance().setText("Points: " + std::to_string(points),0,0);
        luigi->tick(keys);

    }
}