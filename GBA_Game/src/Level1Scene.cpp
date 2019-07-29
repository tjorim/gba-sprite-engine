//
// Created by Wout Briels on 29/11/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
// Header files for scene transition.
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "DeadScene.h"
#include "EndScene.h"
// Data for background drawing.
#include "BG_data.h"
// Sprite data.
#include "Sprite.h"
// Data shared over all scenes.
#include "SharedData.h"
// Level1Scene data (move permissions).
#include "MapData_L1.h"

MapData_L1 mapDataL1;


std::vector<Background *> Level1Scene::backgrounds() {
    return {
        bg.get()
    };
}

std::vector<Sprite *> Level1Scene::sprites() {
    return{
        player.get(),
        coin.get()
    };
}

void Level1Scene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg_palette, sizeof(bg_palette)));

    SpriteBuilder<Sprite> builder;
    player = builder
            .withData(player_data, sizeof(player_data))
            .withSize(SIZE_16_32)
            .withAnimated(4, 5)
            .withLocation(10, GBA_SCREEN_HEIGHT - 32 - 5*16)
            .buildPtr();
    coin= builder
            .withData(coin_data, sizeof(coin_data))
            .withSize(SIZE_8_8)
            .withAnimated(6, 8)
            .buildPtr();

    coinNr = 1;
    level = 1;
    TextStream::instance().setText("Level2", 0, 0);

    // Display: health status.
    std::string healthStr = std::to_string(health);
    TextStream::instance().setText("Health:", 0, 12);
    TextStream::instance().setText(healthStr+"/3", 0, 19);

    bg = std::unique_ptr<Background>(new Background(1, background_data, sizeof(background_data), map1, sizeof(map1)));
    bg.get()->useMapScreenBlock(16);
}

void Level1Scene::tick(u16 keys) {
    // Display: coin status.
    TextStream::instance().setText("Coins:", 1, 0);
    std::string coinPoints = std::to_string(coinNr-1);
    TextStream::instance().setText(coinPoints+"/5", 1, 6);

    // Disable animation while player not moving.
    player->stopAnimating();

    // Background scrolling.
    bg.get()->scroll(bgX, bgY);

    // Position of coin.
    mapDataL1.setCoinPositionX(coinNr);
    mapDataL1.setCoinPositionY(coinNr);
    coin.get()->moveTo(mapDataL1.getCoinPositionX()-bgX, mapDataL1.getCoinPositionY()-bgY);

    // Collision detection between player en coin.
    if (player.get()->collidesWith(*coin)) {
        coinNr++;
    }

    // Coordinates of player on screen.
    playerX = player.get()->getX();
    playerY = player.get()->getY();

    // Coordinates of player on full map (needed for mapDataL1).
    playerOnMapX = playerX + bgX;
    playerOnMapY = playerY + bgY;

    // Get ground level of map.
    mapDataL1.createGroundLevel(playerOnMapX, playerOnMapY+player.get()->getHeight());
    int groundLevelY = mapDataL1.getGroundLevel();

    // Get top level (height player can jump).
    mapDataL1.createTopLevel(playerOnMapX, playerOnMapY);
    int topLevelY = mapDataL1.getTopLevel();

    // Get permission to move in x direction.
    mapDataL1.createBarrierL(playerOnMapX, playerOnMapY+player.get()->getHeight());
    bool movePermissionL = mapDataL1.getMovePermissionL();
    mapDataL1.createBarrierR(playerOnMapX, playerOnMapY+player.get()->getHeight());
    bool movePermissionR = mapDataL1.getMovePermissionR();


    // Enables/disables jumping when player is above (in air) or below (in hole) ground level.
    if (playerOnMapY == groundLevelY-player.get()->getHeight()) {
        jumpingDisabled = false;
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

    // Move in x direction when key LEFT and key RIGHT.
    if (keys & KEY_LEFT) {
        player->animate();
        player->flipHorizontally(true);

        if (movePermissionL) {      // Check if there is no barrier when walking to the left.
            if (player->getX() > 50 || playerX <= 50 && bgX == 0) {
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
                player.get()->moveTo(playerX + 1, playerY);
            } else if (bgX < 16){
                bgX += 1;
            }
        }
    } else {
            player->animateToFrame(0);
    }

    // Teleport player.
    if (playerOnMapX == 224 && playerOnMapY == 208) {
        playerOnMapY = 60;  //64
        bgY -= 64;
        player.get()->moveTo(playerX, playerOnMapY-bgY);
        player.get()->flipHorizontally(true);
    } else if (coinNr == 6 && playerOnMapX == 16 && playerOnMapY == 16) {
        engine->transitionIntoScene(new EndScene(engine), new FadeOutScene(2));
    }

    // When in hole -> player died.
    if (groundLevelY == 300 && playerOnMapY == groundLevelY-player.get()->getHeight()) {
        engine->transitionIntoScene(new DeadScene(engine), new FadeOutScene(2));
    }
}