//
// Created by Tom Fierens on 7/12/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "Space_Kirby_scene.h"
#include "SplashBackground.h"
#include "Space_kirby_sprites.h"
#include "SplashScreen.h"
#include "Death_scene.h"
#include "deadSound.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

Space_Kirby_scene::Space_Kirby_scene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}
std::vector<Sprite *> Space_Kirby_scene::sprites() {
    std::vector<Sprite*> sprites;
    sprites.push_back(Kirby.get());
    for(int i =0; i < 4; ++i) {
        sprites.push_back(platforms[i].get());
    }


    sprites.push_back(enemy.get());

    //sprites.push_back(bubble.get());

    return sprites;
}

std::vector<Background *> Space_Kirby_scene::backgrounds() {
    return {
            bg.get()
    };
}
void Space_Kirby_scene::tick(u16 keys) {
    if(!dead) {
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


        } else {


            if (!Kirby->collideFromAbove(*platforms[0]) && !Kirby->collideFromAbove(*platforms[1]) &&
                !Kirby->collideFromAbove(*platforms[2]) && !Kirby->collideFromAbove(*platforms[3]) &&
                Kirby->getY() < 128) {
                jumping = true;
            }

        }
        if (Kirby->getY() < middenHoogte) {
            score = score - dy;
            for (int i = 0; i < 4; i++) {
                Kirby->moveTo(Kirby->getX(), middenHoogte);
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
        if (platforms[3]->getX() >= 208) { platforms[3]->setVelocity(-1, 0); }
        else if (platforms[3]->getX() <= 0) { platforms[3]->setVelocity(1, 0); }
        if (enemy->getY() > 160) {
            enemy->moveTo(rand() % 208, 0);

        }
        if (Kirby->KirbyCollide(*enemy) || Kirby->getY()>=128) {
            engine.get()->enqueueSound(deadSound, deadSound_bytes);
            engine->stopTransitioning();
            if (!engine->isTransitioning()) {
                dead = true;
                Kirby->makeAnimated(9, 16, 3);
                bg->clearData();
                engine->transitionIntoScene(new Death_scene(engine, score), new FadeOutScene(2));



            }


        }
    }


}

void Space_Kirby_scene::load() {

    engine.get()->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(splashimagePal, sizeof(splashimagePal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));



    SpriteBuilder<Sprite> builder;
    Kirby = builder
            .withData(totaalKirbyTiles, sizeof(totaalKirbyTiles))
            .withSize(SIZE_32_32)


            .withLocation(240 / 2 -16 , 120 - 32)
            .buildPtr();
    Kirby->setStayWithinBounds(true);
    platforms [3] = builder
            .withData(platformTiles, sizeof(platformTiles))
            .withSize(SIZE_32_16)
                    //.withAnimated(8, 3)

            .withLocation(104 , 40 * 3)
            .buildPtr();
    platforms[3]->stopAnimating();
    platforms[3]->setStayWithinBounds(false);
    for(int i =0; i < 3; ++i) {

         platforms [i] = builder
                 .withData(platformTiles, sizeof(platformTiles))
                 .withSize(SIZE_32_16)


                 .withLocation(rand() % 120 + platforms[i + 1]->getX() - 60 , 40 * i)
                 .buildPtr();
         platforms[i]->stopAnimating();
        if (platforms[i]->getX() > 208){platforms[i]->moveTo(178, 40 * i);}
        else if (platforms[i]->getX() < 0){platforms[i]->moveTo(30, 40 * i);}
        platforms[i]->setStayWithinBounds(false);
    }

    enemy = builder
            .withData(enemyTiles, sizeof(enemyTiles))
            .withSize(SIZE_32_32)


            .withLocation(0 , 0)
            .buildPtr();
    enemy->setStayWithinBounds(false);
    enemy->setVelocity(0,1);

    bg = std::unique_ptr<Background>(new Background(0, splashimageTiles, sizeof(splashimageTiles), splashimageMap, sizeof(splashimageMap)));
    jumping = false;
    dead = false;
    dy = 0;
    middenHoogte = 80 -16;
    score = 0;

    bg.get()->useMapScreenBlock(24);



}