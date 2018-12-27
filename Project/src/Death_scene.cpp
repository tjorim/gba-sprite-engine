//
// Created by Tom Fierens on 26/12/2018.
//

#include <memory>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "Death_scene.h"
#include "SplashBackground.h"
#include "theme_song.h"
#include "Space_Kirby_scene.h"
#include "SplashScreen.h"

//Death_scene::Death_scene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> Death_scene::sprites() {
    return {

    };
}

std::vector<Background *> Death_scene::backgrounds() {
    return {

    };
}
void Death_scene::tick(u16 keys) {
    if(keys & KEY_SELECT) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new SplashScreen(engine), new FadeOutScene(2));
            TextStream::instance().clear();

        }
    }
    if(keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new Space_Kirby_scene(engine), new FadeOutScene(2));
            TextStream::instance().clear();

        }
    }

}

void Death_scene::load() {

    engine.get()->enableText();
    TextStream::instance().setText(std::string("GAME OVER"), 5, 10);
    TextStream::instance().setText(std::string("Score: ") + std::to_string(death_score), 10, 10);
    TextStream::instance().setText(std::string("START:"), 15, 4);
    TextStream::instance().setText(std::string("Restart"), 17, 4);
    TextStream::instance().setText(std::string("SELECT:"), 15, 17);
    TextStream::instance().setText(std::string("Menu"), 17, 17);
    engine.get()->enqueueMusic(Mono_wii_song, Mono_wii_song_bytes);

}