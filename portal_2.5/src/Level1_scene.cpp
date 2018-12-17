#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level1_scene.h"
#include "Level1_background.h"
#include "Scene_sprites.h"
#include "Portal_music.h"
#include "Portal_gun_sound.h"



std::vector<Sprite *> Level1_scene::sprites() {
    std::vector<Sprite*> sprites;
    if (redBullet != NULL){
        sprites.push_back(red_bullet_sprite.get());
    }
    if (blueBullet != NULL){
        sprites.push_back(blue_bullet_sprite.get());
    }

    for(auto& s : verticalPortalWallVec) {
        sprites.push_back(s.get());
    }
    for(auto& s : horizontalPortalWallVec) {
        sprites.push_back(s.get());
    }

    for(auto& s : verticalWallVec) {
        sprites.push_back(s.get());
    }

    for(auto& s : horizontalWallVec) {
        sprites.push_back(s.get());
    }

    //sprites.push_back(verticalPortalWallVec[1]);

    sprites.push_back(verticalRedPortal.get());
    sprites.push_back(chell.get());
    sprites.push_back(visier.get());
    return {sprites};
}

std::vector<Background *> Level1_scene::backgrounds() {
    return {
            bg.get()
    };
}

void Level1_scene::moveChell(u16 keys) {
    int xSnelheid  = 0;
    int ySnelheid  = 1;

    if (chell->collidesWith(*verticalRedPortal.get())){
        chell->moveTo(0, 0);
    }
    if (keys & KEY_LEFT) {
        xSnelheid = -1;
    }

    if (keys & KEY_RIGHT) {
        xSnelheid = 1;
    }
    if (keys & KEY_A) {
        ySnelheid = -1;
    }
    if (keys & KEY_B) {
        ySnelheid = 1;
    }

    /*// jump AND gravity
    if (keys & KEY_A && chell->getVelocity().y == 0) {
        if(jump == false) {
            ySnelheid = -2;
            jump = true;
            chellY = chell->getY();
        }
    }
    if(jump == true){
        ySnelheid = -2;
    }

    if( chell->getY()<= chellY-50){
        jump == false;
        ySnelheid = 1;
    }*/

    //Collision detection
    for(auto& s : verticalPortalWallVec) {
        if (chell->collidesWith(*s)){
            if (chell->getX() < s->getX()){
                if (xSnelheid > 0) { xSnelheid = 0; }
            }
            if (chell->getX() > s->getX()){
                if (xSnelheid < 0) { xSnelheid = 0; }
            }
        }
    }
    for(auto& k : horizontalPortalWallVec) {
        if (chell->collidesWith(*k)){
            if (chell->getY() < k->getY()){
                if (ySnelheid > 0) { ySnelheid = 0; }
            }
            if (chell->getY() > k->getY()){
                if (ySnelheid < 0) { ySnelheid = 0; }
            }
        }
    }

    for(auto& s : verticalWallVec) {
        if (chell->collidesWith(*s)){
            if (chell->getX() < s->getX()){
                if (xSnelheid > 0) { xSnelheid = 0; }
            }
            if (chell->getX() > s->getX()){
                if (xSnelheid < 0) { xSnelheid = 0; }
            }
        }
    }
    for(auto& k : horizontalWallVec) {
        if (chell->collidesWith(*k)){
            if (chell->getY() < k->getY()){
                if (ySnelheid > 0) { ySnelheid = 0; }
            }
            if (chell->getY() > k->getY()){
                if (ySnelheid < 0) { ySnelheid = 0; }
            }
        }
    }

    chell->setVelocity(xSnelheid,ySnelheid);
    visier->setVelocity(xSnelheid,ySnelheid);


}


void Level1_scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;

    chell = builder
            .withData(chellTiles, sizeof(chellTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(50,50)
            .buildPtr();

    for(auto& s : verticalPortalWallCoordinaten) {
        verticalPortalWall = builder
                .withData(Vertical_shootableTiles, sizeof(Vertical_shootableTiles))
                .withSize(SIZE_8_32)
                .withLocation(s[0],s[1])
                .buildPtr();
        verticalPortalWallVec.push_back(std::move(verticalPortalWall));
    }

    for(auto& s : horizontalPortalWallCoordinaten) {
        horizontalPortalWall = builder
                .withData(Horizontal_shootable_wallTiles, sizeof(Horizontal_shootable_wallTiles))
                .withSize(SIZE_32_8)
                .withLocation(s[0],s[1])
                .buildPtr();
        horizontalPortalWallVec.push_back(std::move(horizontalPortalWall));
    }

    for(auto& s : verticalWallCoordinaten) {
        verticalWall = builder
                .withData(Vertical_wallTiles, sizeof(Vertical_wallTiles))
                .withSize(SIZE_8_32)
                .withLocation(s[0],s[1])
                .buildPtr();
        verticalWallVec.push_back(std::move(verticalWall));
    }

    for(auto& s : horizontalWallCoordinaten) {
        horizontalWall = builder
                .withData(Horizontal_wallTiles, sizeof(Horizontal_wallTiles))
                .withSize(SIZE_32_8)
                .withLocation(s[0],s[1])
                .buildPtr();
        horizontalWallVec.push_back(std::move(horizontalWall));
    }

    verticalRedPortal = builder
            .withData(Vertical_red_portalTiles, sizeof(Vertical_red_portalTiles))
            .withSize(SIZE_8_32)
            .withLocation(-16,-16)
            .buildPtr();

    verticalBluePortal = builder
            .withData(Vertical_red_portalTiles, sizeof(Vertical_red_portalTiles))
            .withSize(SIZE_8_32)
            .withLocation(-16,-16)
            .buildPtr();

    visier = affineBuilder
            .withData(VisierTiles, sizeof(VisierTiles))
            .withSize(SIZE_64_64)
            .withLocation(50-24,50-24)
            .buildPtr();
    visierRotation = 0;

    red_bullet_sprite = builder.withData(red_bulletTiles, sizeof(red_bulletTiles))
            .withSize(SIZE_8_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();

    blue_bullet_sprite = builder.withData(blue_bulletTiles, sizeof(blue_bulletTiles))
            .withSize(SIZE_8_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);

    redBullet = std::unique_ptr<Portal_bullet>(new Portal_bullet());
    blueBullet = std::unique_ptr<Portal_bullet>(new Portal_bullet());


    //engine->enqueueMusic(Still_Alive, 1412466, 88200);
}

void Level1_scene::tick(u16 keys) {

    // check direction scope
    if (visier->getMatrix()->pa < 0) {
        flip_visier = true;
    } else { flip_visier = false; }

    moveChell(keys);

    //rotate scope
    if (keys & KEY_R) {
        visierRotation -= 200;
    } else if (keys & KEY_L) {
        visierRotation += 200;
    }
    visier->rotate(visierRotation);

    //Shoot gun AND bullet update
    if ((keys & KEY_UP) && (blueBullet->getIsMoving() == false)) {
        red_bullet_sprite->moveTo(visier->getX() + 28, visier->getY() + 28);
        redBullet->setDestination(visier->getMatrix()->pc, visier->getX(), visier->getY(), visier->getWidth());
        redBullet->start(flip_visier, red_bullet_sprite->getX(), red_bullet_sprite->getY());
        redBullet->setIsMoving(true);
    }

    if ((keys & KEY_DOWN) && (redBullet->getIsMoving() == false)) {
        blue_bullet_sprite->moveTo(visier->getX() + 28, visier->getY() + 28);
        blueBullet->setDestination(visier->getMatrix()->pc, visier->getX(), visier->getY(), visier->getWidth());
        blueBullet->start(flip_visier, blue_bullet_sprite->getX(), blue_bullet_sprite->getY());
        blueBullet->setIsMoving(true);
    }

    if(redBullet->getIsMoving() == true && (teller%5 == 0)) {
        redBullet->tick();
        red_bullet_sprite->moveTo(redBullet->getx(), redBullet->gety());
    }
    if(blueBullet->getIsMoving() == true && (teller%5 == 0)) {
        blueBullet->tick();
        blue_bullet_sprite->moveTo(blueBullet->getx(), blueBullet->gety());
    }
teller = teller+1;
    if(red_bullet_sprite->isOffScreen()){
        redBullet->setIsMoving(false);
        red_bullet_sprite->moveTo(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT);
    }

    if(blue_bullet_sprite->isOffScreen()){
        blueBullet->setIsMoving(false);
        blue_bullet_sprite->moveTo(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT);
    }



    //Create portals
    for(auto& s : verticalPortalWallVec) {
        if (red_bullet_sprite->collidesWith(*s)) {
            TextStream::instance().setText(std::to_string(1), 1, 1);
            verticalRedPortal->moveTo(s->getX(), s->getY());
            s->animateToFrame(1);
        }
    }

    for(auto& s : verticalPortalWallVec) {
        if (red_bullet_sprite->collidesWith(*s)) {
            TextStream::instance().setText(std::to_string(1), 1, 1);
            verticalBluePortal->moveTo(s->getX(), s->getY());
            s->animateToFrame(1);
        }
    }
}

