//
// Created by Tom Fierens on 26/12/2018.
//

#include <memory>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include "death_scene.h"
#include "background_image.h"
#include "theme_song.h"
#include "space_Kirby_game_scene.h"
#include "start_screen.h"

//death_scene::death_scene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> death_scene::sprites() {
    return {

    };
}

std::vector<Background *> death_scene::backgrounds() {
    return {

    };
}
//Stay stand-by for key input
void death_scene::tick(u16 keys) {
    if(keys & KEY_SELECT) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new start_screen(engine), new FadeOutScene(2));
            TextStream::instance().clear();

        }
    }
    if(keys & KEY_START) {
        engine->stopTransitioning();
        if (!engine->isTransitioning()) {
            engine->transitionIntoScene(new space_Kirby_game_scene(engine), new FadeOutScene(2));
            TextStream::instance().clear();

        }
    }

}
//Load text, score and music
void death_scene::load() {

    engine.get()->enableText();
    TextStream::instance().setText(std::string("GAME OVER"), 5, 10);
    TextStream::instance().setText(std::string("Score: ") + std::to_string(death_score), 10, 10);
    TextStream::instance().setText(std::string("START:"), 15, 4);
    TextStream::instance().setText(std::string("Restart"), 17, 4);
    TextStream::instance().setText(std::string("SELECT:"), 15, 17);
    TextStream::instance().setText(std::string("Menu"), 17, 17);
    engine.get()->enqueueMusic(Mono_wii_song, Mono_wii_song_bytes);

}