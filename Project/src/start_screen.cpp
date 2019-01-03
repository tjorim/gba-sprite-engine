//
// Created by Tom Fierens on 7/12/2018.
//
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include "start_screen.h"
#include "space_Kirby_game_scene.h"
#include "background_image.h"
#include "start_screen_palette.h"
#include "theme_song.h"
#include "startscene_Kirby.h"
#include "press_start.h"
#include "Kirby_title.h"
#include "space_title.h"


start_screen::start_screen(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

//Initiate sprites
std::vector<Sprite *> start_screen::sprites() {
    return {
        kirby.get(),
        press_start.get(),
        kirby_title.get(),
        space_title.get()
    };
}

//Initiate background
std::vector<Background *> start_screen::backgrounds() {
    return {
            bg.get()
    };
}

void start_screen::tick(u16 keys) {
    if(keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            bg->clearMap();
            engine->transitionIntoScene(new space_Kirby_game_scene(engine), new FadeOutScene(2));
        }
    }
}

void start_screen::load() {

    // Initiating palettes
    engine.get()->disableText();
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(backgroundPal, sizeof(backgroundPal)));
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    //Building sprites
    SpriteBuilder<Sprite> builder;
    kirby = builder
            .withData(flying_KirbyTiles, sizeof(flying_KirbyTiles))
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

    //Building background
    bg = std::unique_ptr<Background>(new Background(0, backgroundTiles, sizeof(backgroundTiles), backgroundMap, sizeof(backgroundMap)));
    bg.get()->useMapScreenBlock(24);

    //Start music
    engine.get()->enqueueMusic(Mono_wii_song, Mono_wii_song_bytes);

}