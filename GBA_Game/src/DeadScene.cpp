//
// Created by Wout Briels on 3/01/2019.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "DeadScene.h"
#include "Level2Scene.h"

#include "Player.h"

Player p;

std::vector<Background *> DeadScene::backgrounds() {
    return {};
}

std::vector<Sprite *> DeadScene::sprites() {
    return{};
}

void DeadScene::load() {
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager());
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager());

    TextStream::instance().setText("You died!", 9, 10);
    TextStream::instance().setText("Press Start to restart.", 11, 5);

    health = p.getHealth();
    health--;
    p.setHealth(health);
}

void DeadScene::tick(u16 keys) {
    if (keys & KEY_START) {
        engine->transitionIntoScene(new Level2Scene(engine), new FadeOutScene(2));
    }

    std::string healthStr = std::to_string(health);
    TextStream::instance().setText(healthStr, 0, 0);
}