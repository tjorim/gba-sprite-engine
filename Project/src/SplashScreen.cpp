//
// Created by Tom Fierens on 7/12/2018.
//
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "SplashScreen.h"
#include "Space_Kirby_scene.h"

#include "SplashBackground.h"
#include "splash_sprites.h"
#include "theme_song.h"
#include "splash_background_test.h"

SplashScreen::SplashScreen(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> SplashScreen::sprites() {
    return {
        kirby.get(),
        press_start.get(),
        kirby_title.get(),
        space_title.get()
    };
}

std::vector<Background *> SplashScreen::backgrounds() {
    return {
            bg.get()
    };
}
void SplashScreen::tick(u16 keys) {
    if(keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new Space_Kirby_scene(engine), new FadeOutScene(2));
            bg->clearMap();

        }

    }
}

void SplashScreen::load() {

    // we need to disable the text background because the splash screen is too big and fills up al char blocks (including map)
    // remember, we have background char blocks 0, 1, 2, 3, each consisting of 8 screen blocks, from 0x6000000 to 0x6000f800 (last screen block, 31)
    engine.get()->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(splashimagePal, sizeof(splashimagePal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    // use background number 0, as the text bg is disabled, to start dumping into VRAM from 0x6000000
    // data exported from grit using: "grit splashimage.png -gt -gB8 -mRtpf -mLs -ftc", see https://www.coranac.com/man/grit/html/grit.htm or https://github.com/devkitPro/grit/blob/master/grit-readme.txt
    // do NOT use "-Mw" or "-Mh", regular map needed, no metamap.
    SpriteBuilder<Sprite> builder;
    kirby = builder
            .withData(SpritesetKirbyTiles, sizeof(SpritesetKirbyTiles))
            .withSize(SIZE_32_32)
            .withAnimated(0,8, 3)
            .withLocation(240 / 2 -16 , 160 / 2 -16)
            .buildPtr();
    press_start = builder
            .withData(press_startTiles, sizeof(press_startTiles))
            .withSize(SIZE_64_32)

            .withLocation(240 / 2 -20 , 160 / 2 +30)
            .buildPtr();
    kirby_title = builder
            .withData(kirby_titleTiles, sizeof(kirby_titleTiles))
            .withSize(SIZE_64_32)
            .withLocation(240 / 2  , 160 / 2 -48)
            .buildPtr();
    space_title = builder
            .withData(space_titleTiles, sizeof(space_titleTiles))
            .withSize(SIZE_64_32)
            .withLocation(240 / 2  -64, 160 / 2 -48)
            .buildPtr();
    // the photograph was first edited in GIMP to contain max. 255 colors using image -> mode -> indexed colors.
    bg = std::unique_ptr<Background>(new Background(0, splashimageTiles, sizeof(splashimageTiles), splashimageMap, sizeof(splashimageMap)));

    // the last char block (3) starts at screen block 24, is still available to dump the tilemap in.
    bg.get()->useMapScreenBlock(24);

    engine.get()->enqueueMusic(Mono_wii_song, Mono_wii_song_bytes);

}