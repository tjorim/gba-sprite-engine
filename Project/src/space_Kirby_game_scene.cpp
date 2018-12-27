//
// Created by Tom Fierens on 7/12/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "space_Kirby_game_scene.h"
#include "background_image.h"
#include "space_kirby_game_sprites.h"
#include "start_screen.h"
#include "death_scene.h"
#include "dead_sound.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

space_Kirby_game_scene::space_Kirby_game_scene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

//Initiate sprites
std::vector<Sprite *> space_Kirby_game_scene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(Kirby.get());
    for(int i =0; i < 4; ++i) {
        sprites.push_back(platforms[i].get());
    }
    sprites.push_back(enemy.get());
    return sprites;
}

//Initiate background
std::vector<Background *> space_Kirby_game_scene::backgrounds() {
    return {
            bg.get()
    };
}


void space_Kirby_game_scene::tick(u16 keys) {
    if(!dead) {
        //Checking key input for movement
        if (keys & KEY_A) {

            if (!jumping) {

                jumping = true;
                dy = -5;
            }
        }
        if (keys & KEY_LEFT) {

            Kirby->makeAnimated(0, 8, 3);
            Kirby->flipHorizontally(true);
            Kirby->moveTo(Kirby->getX() - 2, Kirby->getY());
        } else if (keys & KEY_RIGHT) {

            Kirby->makeAnimated(0, 8, 3);
            Kirby->flipHorizontally(false);
            Kirby->moveTo(Kirby->getX() + 2, Kirby->getY());
        } else {

            Kirby->makeAnimated(0, 2, 8);
        }
        //Jump movement
        if (jumping) {


            dy = dy + 0.2;
            Kirby->moveTo(Kirby->getX(), Kirby->getY() + dy);
            Kirby->makeAnimated(16, 18, 6);
            for (int i = 0; i < 4; ++i) {
                if ((Kirby->collideFromAbove(*platforms[i]) && dy > 0)) {
                    Kirby->moveTo(Kirby->getX(), platforms[i]->getY() - Kirby->getHeight());
                    jumping = false;
                    dy = 0;

                }
            }

        //Movement on platform
        } else {


            if (!Kirby->collideFromAbove(*platforms[0]) && !Kirby->collideFromAbove(*platforms[1]) &&
                !Kirby->collideFromAbove(*platforms[2]) && !Kirby->collideFromAbove(*platforms[3]) &&
                Kirby->getY() < 128) {
                jumping = true;
            }

        }
        //Updating platform scroll and score
        if (Kirby->getY() < scroll_hight) {
            score = score - dy;
            for (int i = 0; i < 4; i++) {
                Kirby->moveTo(Kirby->getX(), scroll_hight);
                platforms[i]->moveTo(platforms[i]->getX(), platforms[i]->getY() - dy);

                if (platforms[i]->getY() > 160) {
                    if (i == 3) {
                        platforms[i]->moveTo(rand() % 120 + platforms[0]->getX() - 60, 0);
                        if (platforms[i]->getX() > 208) { platforms[i]->moveTo(178, 0); }
                        else if (platforms[i]->getX() < 0) { platforms[i]->moveTo(30, 0); }
                        platforms[i]->setVelocity(1, 0);
                    } else if (i == 2) {
                        platforms[i]->moveTo(rand() % 208, 0);
                    } else {
                        platforms[i]->moveTo(rand() % 120 + platforms[i + 1]->getX() - 60, 0);
                        if (platforms[i]->getX() > 208) { platforms[i]->moveTo(platforms[i + 1]->getX(), 0); }
                        else if (platforms[i]->getX() < 0) { platforms[i]->moveTo(platforms[i + 1]->getX(), 0); }
                    }
                }
            }
            enemy->moveTo(enemy->getX(), enemy->getY() - dy);
        }
        //Platform movement
        if (platforms[3]->getX() >= 208) { platforms[3]->setVelocity(-1, 0); }
        else if (platforms[3]->getX() <= 0) { platforms[3]->setVelocity(1, 0); }
        if (enemy->getY() > 160) {

            enemy->moveTo(rand() % 208, 0);
        }
        //Checking for death
        if (Kirby->KirbyCollide(*enemy) || Kirby->getY()>=128) {
            engine.get()->enqueueSound(dead_sound, deadSound_bytes);
            engine->stopTransitioning();
            if (!engine->isTransitioning()) {
                dead = true;
                Kirby->makeAnimated(9, 16, 3);
                bg->clearData();
                engine->transitionIntoScene(new death_scene(engine, score), new FadeOutScene(2));
            }
        }
    }
}

void space_Kirby_game_scene::load() {
    //Setting palettes
    engine.get()->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));


    //Building sprites
    SpriteBuilder<Sprite> builder;

    Kirby = builder
            .withData(complete_KirbyTiles, sizeof(complete_KirbyTiles))
            .withSize(SIZE_32_32)
            .withLocation(240 / 2 -16 , 120 - 32)
            .buildPtr();

    Kirby->setStayWithinBounds(true);

    platforms [3] = builder
            .withData(platformTiles, sizeof(platformTiles))
            .withSize(SIZE_32_16)
            .withLocation(104 , 40 * 3)
            .buildPtr();

    platforms[3]->stopAnimating();

    platforms[3]->setStayWithinBounds(false);

    for(int i =2; i >= 0; --i) {
         platforms [i] = builder
                 .withData(platformTiles, sizeof(platformTiles))
                 .withSize(SIZE_32_16)
                 .withLocation(rand() % 120 + platforms[i + 1]->getX() - 60 , 40 * i)
                 .buildPtr();
         platforms[i]->stopAnimating();
        if (platforms[i]->getX() > 208){platforms[i]->moveTo(platforms[i + 1]->getX(), 40 * i);}
        else if (platforms[i]->getX() < 0){platforms[i]->moveTo(platforms[i + 1]->getX(), 40 * i);}
        platforms[i]->setStayWithinBounds(false);
    }

    enemy = builder
            .withData(enemyTiles, sizeof(enemyTiles))
            .withSize(SIZE_32_32)
            .withLocation(0 , 0)
            .buildPtr();

    enemy->setStayWithinBounds(false);

    enemy->setVelocity(0,1);

    //Building background
    bg = std::unique_ptr<Background>(new Background(0, backgroundTiles, sizeof(backgroundTiles), backgroundMap, sizeof(backgroundMap)));

    //Initiating values an booleans
    jumping = false;
    dead = false;
    dy = 0;
    scroll_hight = 80 -16;
    score = 0;

    bg.get()->useMapScreenBlock(24);

}