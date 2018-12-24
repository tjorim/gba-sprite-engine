//
// Created by Wout Briels on 29/11/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level1Scene.h"
//#include "Bg.h"
//#include "background.h"
#include "BGdata_Level1Scene.h"
#include "MapData.h"

#include "Player.h"

MapData mapData;


std::vector<Background *> Level1Scene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> Level1Scene::sprites() {
    return{
        player.get()
    };
}

void Level1Scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(player_pal, sizeof(player_pal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));


    SpriteBuilder<Sprite> builder;
    //SpriteBuilder<AffineSprite> affineBuilder;

    //smiley = builder.withData(piskelTiles, sizeof(piskelTiles)).withSize(SIZE_16_16).withLocation(10,10).buildPtr();
    //player = affineBuilder.withData(piskel2Tiles, sizeof(piskel2Tiles)).withSize(SIZE_16_16).withLocation(10, 133).buildPtr();
    player = builder
            .withData(player_data, sizeof(player_data))
            .withSize(SIZE_16_32)
            .withAnimated(4, 5)
            .withLocation(10, GBA_SCREEN_HEIGHT - 32 - 5*16)
            .buildPtr();


    //TextStream::instance() << "Ooh boy!! That was ez shit";

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map, sizeof(map)));
    bg.get()->useMapScreenBlock(16);
    //bg.get()->scroll(0, 95);
}

void Level1Scene::tick(u16 keys) {

    // Coordinates of player on screen.
    playerX = player.get()->getX();
    playerY = player.get()->getY();

    // Coordinates of player on full map (needed for mapData).
    playerOnMapX = playerX + bgX;
    playerOnMapY = playerY + bgY;

    // Scroll bg in x direction when player is 50 from barrier.
    bg.get()->scroll(bgX, bgY);

    player->stopAnimating();

    // Stops background from infinite scrolling. !!!(not necessary anymore)!!!
    /*
    if (bgX > 16) {
        bgX = 16;
    } else if (bgX <0) {
        bgX = 0;
    }
    */


    // Set player to ground level.
    mapData.createGroundLevel(playerOnMapX, playerOnMapY+player.get()->getHeight());     // Set y-coor for ground level at each x-coor
    int groundLevelY = mapData.getGroundLevel();        // Get y-coor of ground level

    // Get top level (height player can jump).
    mapData.createTopLevel(playerOnMapX, playerOnMapY);
    int topLevelY = mapData.getTopLevel();

    // Get permission to move in x direction.
    mapData.createBarrierL(playerOnMapX, playerOnMapY+player.get()->getHeight());
    bool movePermissionL = mapData.getMovePermissionL();
    mapData.createBarrierR(playerOnMapX, playerOnMapY+player.get()->getHeight());
    bool movePermissionR = mapData.getMovePermissionR();


    // Enables/disables jumping when player is above (in air) or below (in hole) ground level.
    if (playerOnMapY == groundLevelY-player.get()->getHeight()) {
        jumpingDisabled = false;
    } else if (playerOnMapY > groundLevelY-player.get()->getHeight()) {  // When in hole.
        jumpingDisabled = true;
    } else if (playerOnMapY <= groundLevelY-player.get()->getHeight()-28) {  // 28: value of jump height
        jumpingDisabled = true;
    }

    // Provides gravity.
    if (playerOnMapY < groundLevelY-player.get()->getHeight()) {        // Checks if player is standing on ground level.
        // Provides background scrolling when player is falling.
        if (player.get()->getY() < GBA_SCREEN_HEIGHT-player.get()->getHeight()-32 || playerY >= GBA_SCREEN_HEIGHT-player.get()->getHeight()-32 && bgY == 96) {
            player.get()->setVelocity(0, 2);                            // Gravity!!
        } else if (bgY < 96) {
            player.get()->setVelocity(0, 0);
            bgY += 2;
        }

    } else {
        player.get()->setVelocity(0, 0);
    }

    // Disables jumping when player head collides with top level.
    if (playerOnMapY <= topLevelY) {
        jumpingDisabled = true;
    }

    // Jump when key UP.
    if (keys & KEY_UP && !jumpingDisabled) {
        if (player.get()->getY() > 32 || playerY <= 32 && bgY == 0) {
            player.get()->setVelocity(0, -4);
        } else if (bgY > 0) {
            player.get()->setVelocity(0, 0);
            bgY -= 4;
        }
    }


/*
    // REMOVE !!!
    if (keys & KEY_UP) {
        if (player.get()->getY() > 32 || playerY <= 32 && bgY == 0) {
            //player.get()->moveTo(playerX, playerY-1);
            player.get()->setVelocity(0, -1);
        } else if (bgY > 0) {
            player.get()->setVelocity(0, 0);
            bgY -= 1;
        }
    } else if (keys & KEY_DOWN) {
        if (playerOnMapY < groundLevelY-player.get()->getHeight()) {
            if (player.get()->getY() < GBA_SCREEN_HEIGHT - player.get()->getHeight() - 32 ||
                playerY >= GBA_SCREEN_HEIGHT - player.get()->getHeight() - 32 && bgY == 96) {
                player.get()->setVelocity(0, 1);
            } else if (bgY < 96) {
                player.get()->setVelocity(0, 0);
                bgY += 1;
            }
        } else {
            player.get()->setVelocity(0, 0);
        }
    } else {
        player.get()->setVelocity(0, 0);
    }
    // REMOVE !!!
*/

    // Move in x direction when key LEFT and key RIGHT.
    if (keys & KEY_LEFT) {
        player->animate();
        player->flipHorizontally(true);

        if (movePermissionL) {      // Check if there is no barrier when walking to the left.
            if (player->getX() > 50 || playerX <= 50 && bgX == 0) {
                //player->setVelocity(-1, 0);
                player.get()->moveTo(playerX - 1, playerY);
            } else if (bgX > 0){
                bgX -= 1;
            }
        }
    } else if (keys & KEY_RIGHT) {
        player->animate();
        player->flipHorizontally(false);

        if (movePermissionR) {      // Check if there is no barrier when walking to the left.
            if (player->getX() < GBA_SCREEN_WIDTH-50-player.get()->getWidth() || playerX >= GBA_SCREEN_WIDTH-50-player.get()->getWidth() && bgX == 16) {
                //player->setVelocity(+1, 0);
                player.get()->moveTo(playerX + 1, playerY);
            } else if (bgX < 16){
                bgX += 1;
            }
        }
    } else {
            player->animateToFrame(0);
    }

    // For teleporting player from layer 1 to layer 2.
    if (playerOnMapX == 224 && playerOnMapY == 208) {
        playerOnMapY = 60;  //64
        bgY -= 64;
        player.get()->moveTo(playerX, playerOnMapY-bgY);
    }



    // For debugging purposes!!
    if (keys & KEY_A) {     // Key X
        TextStream::instance() << groundLevelY << playerOnMapY;
    } else if (keys & KEY_R) {      // Key S
        TextStream::instance().clear();
    }

}
