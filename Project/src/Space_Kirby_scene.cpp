//
// Created by Tom Fierens on 7/12/2018.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "Space_Kirby_scene.h"
#include "SplashBackground.h"
#include "Space_kirby_sprites.h"
#include <libgba-sprite-engine/background/text_stream.h>

Space_Kirby_scene::Space_Kirby_scene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}
std::vector<Sprite *> Space_Kirby_scene::sprites() {
    std::vector<Sprite*> sprites;

    for(int i =0; i < 4; ++i) {
        sprites.push_back(platforms[i].get());
    }

    sprites.push_back(Kirby.get());

    return sprites;
}

std::vector<Background *> Space_Kirby_scene::backgrounds() {
    return {
            bg.get()
    };
}
void Space_Kirby_scene::tick(u16 keys) {
    if(keys & KEY_A){
        if(!jumping) {
            jumping = true;
            dy = -5;

        }

    }

    if(keys & KEY_LEFT) {

        Kirby->makeAnimated(0,8,3);
        Kirby->flipHorizontally(true);
        Kirby->moveTo(Kirby->getX()-2,Kirby->getY());
    }else if(keys & KEY_RIGHT) {

        Kirby->makeAnimated(0,8,3);
        Kirby->flipHorizontally(false);
        Kirby->moveTo(Kirby->getX()+2,Kirby->getY());
    } else{

        Kirby->makeAnimated(0,2,8);


    }
    if (jumping){


        dy = dy + 0.2;
        Kirby->moveTo(Kirby->getX(),Kirby->getY()+dy);
        Kirby->makeAnimated(16,18,6);
        for(int i =0; i < 4; ++i) {
            if ((Kirby->collideFromAbove(*platforms[i]) && dy > 0) || Kirby->getY() >= 128) {
                Kirby->moveTo(Kirby->getX(), platforms[i]->getY()-Kirby->getHeight());
                jumping = false;
                dy = 0;

            }
        }


    }
    else {



        if (!Kirby->collideFromAbove(*platforms[0]) && !Kirby->collideFromAbove(*platforms[1]) && !Kirby->collideFromAbove(*platforms[2]) && !Kirby->collideFromAbove(*platforms[3]) && Kirby->getY() < 128) {
            jumping = true;
        }

    }
    if(Kirby->getY() < middenHoogte){

        for (int i=0;i<4;i++)
        {
            Kirby->moveTo(Kirby->getX(),middenHoogte);
            platforms[i]->moveTo(platforms[i]->getX(), platforms[i]->getY() - dy);

            if (platforms[i]->getY() > 160) {
                if(i == 3){
                    platforms[i]->moveTo(rand()%110 + platforms[0]->getX() - 55 , 0);
                    if (platforms[i]->getX() > 208){platforms[i]->moveTo(148, 0);}
                    else if (platforms[i]->getX() < 0){platforms[i]->moveTo(60, 0);}
                    platforms[i]->setVelocity(1,0);
                } else {
                    platforms[i]->moveTo(rand() % 110 + platforms[i + 1]->getX() - 55, 0);
                    if (platforms[i]->getX() > 208){platforms[i]->moveTo(148, 0);}
                    else if (platforms[i]->getX() < 0){platforms[i]->moveTo(60, 0);}
                }
            }
        }
    }
    if(platforms[3]->getX()>=208){platforms[3]->setVelocity(-1,0);}
    else if(platforms[3]->getX()<=0){platforms[3]->setVelocity(1,0);}

}

void Space_Kirby_scene::load() {

   //struct point{px,py;};
    //point plat[20];


    // we need to disable the text background because the splash screen is too big and fills up al char blocks (including map)
    // remember, we have background char blocks 0, 1, 2, 3, each consisting of 8 screen blocks, from 0x6000000 to 0x6000f800 (last screen block, 31)
    engine.get()->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(splashimagePal, sizeof(splashimagePal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    // use background number 0, as the text bg is disabled, to start dumping into VRAM from 0x6000000
    // data exported from grit using: "grit splashimage.png -gt -gB8 -mRtpf -mLs -ftc", see https://www.coranac.com/man/grit/html/grit.htm or https://github.com/devkitPro/grit/blob/master/grit-readme.txt
    // do NOT use "-Mw" or "-Mh", regular map needed, no metamap.


    SpriteBuilder<Sprite> builder;

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
                         //.withAnimated(8, 3)

                 .withLocation(rand() % 110 + platforms[i + 1]->getX() - 55 , 40 * i)
                 .buildPtr();;
         platforms[i]->stopAnimating();
        if (platforms[i]->getX() > 208){platforms[i]->moveTo(148, 40 * i);}
        else if (platforms[i]->getX() < 0){platforms[i]->moveTo(60, 40 * i);}
        platforms[i]->setStayWithinBounds(false);
    }
    Kirby = builder
            .withData(totaalKirbyTiles, sizeof(totaalKirbyTiles))
            .withSize(SIZE_32_32)
                    //.withAnimated(8, 3)

            .withLocation(240 / 2 -16 , 160 -32)
            .buildPtr();
    // use background number 0, as the text bg is disabled, to start dumping into VRAM from 0x6000000
    // data exported from grit using: "grit splashimage.png -gt -gB8 -mRtpf -mLs -ftc", see https://www.coranac.com/man/grit/html/grit.htm or https://github.com/devkitPro/grit/blob/master/grit-readme.txt
    // do NOT use "-Mw" or "-Mh", regular map needed, no metamap.
    Kirby->setStayWithinBounds(true);
    // the photograph was first edited in GIMP to contain max. 255 colors using image -> mode -> indexed colors.
    bg = std::unique_ptr<Background>(new Background(0, splashimageTiles, sizeof(splashimageTiles), splashimageMap, sizeof(splashimageMap)));
    jumping = false;
    dy = 0;
    middenHoogte = 80-32;
    score = 0;
    // the last char block (3) starts at screen block 24, is still available to dump the tilemap in.
    bg.get()->useMapScreenBlock(24);



}