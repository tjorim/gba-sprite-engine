#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memmap.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level_scene.h"
#include "Level1_background.h"
#include "Scene_sprites.h"
#include "Portal_music.h"
#include "Portal_gun_sound.h"
#include "Level.h"
#include "WallTile.h"
#include "Portal.h"
#include "Visier.h"



std::vector<Sprite *> Level_scene::sprites() {
    std::vector<Sprite*> sprites;

    sprites.push_back(gameLevel.getChell()->getSprite());
    sprites.push_back(gameLevel.getBlueBullet()->getSprite());
    sprites.push_back(gameLevel.getRedBullet()->getSprite());
    sprites.push_back(gameLevel.getBluePortal()->getVerticalSprite());
    sprites.push_back(gameLevel.getBluePortal()->getHorizontalSprite());
    sprites.push_back(gameLevel.getRedPortal()->getVerticalSprite());
    sprites.push_back(gameLevel.getRedPortal()->getHorizontalSprite());
    sprites.push_back(gameLevel.getVisier()->getSprite());

    for(auto& b : gameLevel.getHorizontalPortalWallVec()) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : gameLevel.getVerticalPortalWallVec()) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : gameLevel.getHorizontalWallVec()) {
        sprites.push_back(b->getSprite());
    }
    for(auto& b : gameLevel.getVerticalWallVec()) {
        sprites.push_back(b->getSprite());
    }

    return {sprites};
}

std::vector<Background *> Level_scene::backgrounds() {
    return {
            bg.get()
    };
}



void Level_scene::load() {
    std::unique_ptr<Sprite> chell, red_bullet_sprite, blue_bullet_sprite, verticalPortalWall, verticalWall, horizontalPortalWall,
            horizontalWall, verticalRedPortal, verticalBluePortal, horizontalRedPortal, horizontalBluePortal,
            button, companionCube;
    std::unique_ptr<AffineSprite> visier;

    std::vector<std::unique_ptr<WallTile>> verticalPortalWallVec, verticalWallVec, horizontalPortalWallVec, horizontalWallVec;

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;



    chell = builder
            .withData(chellTiles, sizeof(chellTiles))
            .withSize(SIZE_16_32)
            .withAnimated(4, 6)
            .withLocation(72,100)
            .buildPtr();
    std::unique_ptr<Chell> chellObject(new Chell(std::move(chell)));

    for(auto& s : verticalPortalWallCoordinaten) {
        verticalPortalWall = builder
                .withData(Vertical_shootableTiles, sizeof(Vertical_shootableTiles))
                .withSize(SIZE_8_32)
                .withLocation(s[0],s[1])
                .buildPtr();

        std::unique_ptr<WallTile> wallObject(new WallTile(std::move(verticalPortalWall)));
        verticalPortalWallVec.push_back(std::move(wallObject));
    }

    for(auto& s : horizontalPortalWallCoordinaten) {
        horizontalPortalWall = builder
                .withData(Horizontal_shootable_wallTiles, sizeof(Horizontal_shootable_wallTiles))
                .withSize(SIZE_32_8)
                .withLocation(s[0],s[1])
                .buildPtr();

        std::unique_ptr<WallTile> wallObject(new WallTile(std::move(horizontalPortalWall)));
        horizontalPortalWallVec.push_back(std::move(wallObject));
    }

    for(auto& s : verticalWallCoordinaten) {
        verticalWall = builder
                .withData(Vertical_wallTiles, sizeof(Vertical_wallTiles))
                .withSize(SIZE_8_32)
                .withLocation(s[0],s[1])
                .buildPtr();

        std::unique_ptr<WallTile> wallObject(new WallTile(std::move(verticalWall)));
        verticalWallVec.push_back(std::move(wallObject));
    }

    for(auto& s : horizontalWallCoordinaten) {
        horizontalWall = builder
                .withData(Horizontal_wallTiles, sizeof(Horizontal_wallTiles))
                .withSize(SIZE_32_8)
                .withLocation(s[0],s[1])
                .buildPtr();

        std::unique_ptr<WallTile> wallObject(new WallTile(std::move(horizontalWall)));
        horizontalWallVec.push_back(std::move(wallObject));
    }

    verticalRedPortal = builder
            .withData(Vertical_red_portalTiles, sizeof(Vertical_red_portalTiles))
            .withSize(SIZE_8_32)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();

    horizontalRedPortal = builder
            .withData(Horizontal_red_portalTiles, sizeof(Horizontal_red_portalTiles))
            .withSize(SIZE_32_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();
    std::unique_ptr<Portal> redPortal(new Portal(std::move(verticalRedPortal), std::move(horizontalRedPortal)));

    verticalBluePortal = builder
            .withData(Vertical_blue_portalTiles, sizeof(Vertical_blue_portalTiles))
            .withSize(SIZE_8_32)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();

    horizontalBluePortal = builder
            .withData(Horizontal_blue_portalTiles, sizeof(Horizontal_blue_portalTiles))
            .withSize(SIZE_32_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();
    std::unique_ptr<Portal> bluePortal(new Portal(std::move(verticalBluePortal), std::move(horizontalBluePortal)));

    visier = affineBuilder
            .withData(VisierTiles, sizeof(VisierTiles))
            .withSize(SIZE_64_64)
            .withLocation(72-24,100-24)
            .buildPtr();
    visierRotation = 0;
    std::unique_ptr<Visier> visierObject(new Visier(std::move(visier)));

    red_bullet_sprite = builder.withData(red_bulletTiles, sizeof(red_bulletTiles))
            .withSize(SIZE_8_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();
    std::unique_ptr<Portal_bullet> bulletObject1(new Portal_bullet(std::move(red_bullet_sprite)));

    blue_bullet_sprite = builder.withData(blue_bulletTiles, sizeof(blue_bulletTiles))
            .withSize(SIZE_8_8)
            .withLocation(GBA_SCREEN_WIDTH,GBA_SCREEN_HEIGHT)
            .buildPtr();
    std::unique_ptr<Portal_bullet> bulletObject2(new Portal_bullet(std::move(blue_bullet_sprite)));


    gameLevel = Level(std::move(chellObject), std::move(verticalPortalWallVec), std::move(verticalWallVec), std::move(horizontalPortalWallVec), std::move(horizontalWallVec),
                                               std::move(redPortal),std::move(bluePortal),std::move(visierObject),std::move(bulletObject1),std::move(bulletObject2));

    visierRotation = 0;

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);



    //engine->enqueueMusic(Still_Alive, 1412466, 88200/4);
}

void Level_scene::tick(u16 keys) {
    bool lKey = false;
    bool rKey = false;
    bool jump = false;

    if(keys & KEY_RIGHT){
        rKey = true;
    }
    if(keys & KEY_LEFT){
        lKey = true;
    }
    if(keys & KEY_UP){
        jump = true;
    }
    gameLevel.moveChell(lKey, rKey, jump);

    if(keys & KEY_R){
        gameLevel.getVisier()->rotate(true);
    }
    if(keys & KEY_L){
        gameLevel.getVisier()->rotate(false);
    }

    if(keys & KEY_A){
        gameLevel.shoot(gameLevel.getRedBullet().get());
    }
    if(keys & KEY_B){
        gameLevel.shoot(gameLevel.getBlueBullet().get());
    }

    gameLevel.update();
    gameLevel.checkPortals();
}






