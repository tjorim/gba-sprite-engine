#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level1_scene.h"
#include "Level1_background.h"
#include "Scene_sprites.h"


std::vector<Sprite *> Level1_scene::sprites() {
    std::vector<Sprite*> sprites;
    if (bullet != NULL){
        sprites.push_back(red_bullet.get());
    }
    sprites.push_back(chell.get());
    sprites.push_back(visier.get());
    return {sprites};
}

std::vector<Background *> Level1_scene::backgrounds() {
    return {
            bg.get()
    };
}

std::unique_ptr<Red_bullet> Level1_scene::createBullet() {
    return std::unique_ptr<Red_bullet>(new Red_bullet(spriteBuilder
    ->withLocation(240, 160)
    .buildWithDataOf(*red_bullet.get())));
}

void Level1_scene::removeBullet(std::unique_ptr<Sprite> &sprite){

}

void Level1_scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;
    spriteBuilder = std::unique_ptr<SpriteBuilder<Sprite>>(new SpriteBuilder<Sprite>);

    chell = builder
            .withData(chellTiles, sizeof(chellTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(30,GBA_SCREEN_HEIGHT - chell->getHeight() - 40)
            .buildPtr();

    visier = affineBuilder
            .withData(VisierTiles, sizeof(VisierTiles))
            .withSize(SIZE_64_64)
            .withLocation(30,GBA_SCREEN_HEIGHT - chell->getHeight() - 40)
            .buildPtr();
    visierRotation = 0;

    red_bullet = spriteBuilder->withData(red_bulletTiles, sizeof(red_bulletTiles))
            .withSize(SIZE_8_8)
            .withLocation(0, 0)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

}

void Level1_scene::tick(u16 keys) {


    if(keys & KEY_R) {
        visierRotation -= 100;
    } else if(keys & KEY_L) {
        visierRotation += 100;
    }

    if(keys & KEY_LEFT) {
        chell->setVelocity(-1, 0);
        visier->setVelocity(-1, 0);
    }

    else if(keys & KEY_RIGHT) {
        chell->setVelocity(1, 0);
        visier->setVelocity(1, 0);
    }
    else{
        chell->setVelocity(0, 0);
        visier->setVelocity(0, 0);
    }


    if((keys & KEY_A)) {
        bullet = createBullet();
        bullet->setDestination({0,100});
        bullet->start();
    }

    visier->rotate(visierRotation);
    bullet->tick();
    red_bullet->moveTo(bullet->getx(), bullet->gety());


    double r = -static_cast<double>(visier->getMatrix()->pb)/(visier->getWidth()*4);

}
