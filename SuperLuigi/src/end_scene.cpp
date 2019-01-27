//
// Created by mathi on 27/01/2019.
//

#include "end_scene.h"
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/text_stream.h>

#include "background.h"
#include "LuigiTiles.h"
#include "bowserTiles.h"
#include "sharedPal.h"
#include "Luigi.h"
#include "bowser.h"

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

    bowserSprite = affineBuilder
            .withData(bowserTiles,sizeof(bowserTiles))
            .withSize(SIZE_32_32)
            .withLocation(GBA_SCREEN_WIDTH-32,GBA_SCREEN_HEIGHT-bottomHeightFor32)
            .withAnimated(0,0)
            .buildPtr();
    Bowser = std::unique_ptr<bowser>{new bowser(std::move(bowserSprite))};
    Bowser->getBowserSprite()->stopAnimating();
    Bowser->timer();

}
std::vector<Sprite *> end_scene::sprites() {

    std::vector<Sprite *> sprites;
    sprites.push_back(luigi->getLuigiSprite().get());
    sprites.push_back(Bowser->getBowserSprite().get());
    return sprites;
}

void end_scene::tick(u16 keys) {
    if(!luigi->isDead() ) {
        TextStream::instance().setText("Points: " + std::to_string(points)+ " BowserLives: " +std::to_string(Bowser->getLives()) ,0,0);
        Bowser->tick(keys);
        luigi->tickEndScene(keys);

        if(luigi->getLuigiSprite()->collidesWith(*Bowser->getBowserSprite()) && luigi->getLuigiSprite()->getY() == Bowser->getBowserSprite()->getY() - 30
            && luigi->getLuigiSprite()->getVelocity().y >0){

            Bowser->subtractLife();
            if(Bowser->getLives() == 0) Bowser->kill();
        }

    }
}