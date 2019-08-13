//
// Created by tiele on 9/08/2019.
//

#include "profile_scene.h"

ProfileScene::ProfileScene(const std::shared_ptr<GBAEngine> &engine) : Scene(engine) {}

std::vector<Sprite *> ProfileScene::sprites() {
    return std::vector<Sprite *>();
}

std::vector<Background *> ProfileScene::backgrounds() {
    return std::vector<Background *>();
}

void ProfileScene::load() {

}

void ProfileScene::tick(u16 keys) {

}
