//
// Created by Jolien Jeunen on 25/01/2019.
//

#ifndef TESTGAME_MAINSCENE_H
#define TESTGAME_MAINSCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>

class MainScene : public Scene {
private:
    std::unique_ptr<AffineSprite> BirdSprite;
    std::unique_ptr<Sprite> BuisSprite1;
    std::unique_ptr<Sprite> BuisSprite2;

    std::unique_ptr<Sprite> BuisSprite3;
    std::unique_ptr<Sprite> BuisSprite4;
    std::unique_ptr<Sprite> BuisSprite5;
    std::unique_ptr<Sprite> BuisSprite6;

    std::unique_ptr<Sprite> BuisSprite7;
    std::unique_ptr<Sprite> BuisSprite8;
    std::unique_ptr<Background> bg;

    int scrollX, scrollY;
    double birdY,birdX;
    int scrollBuisX, scrollBuisY;


public:
    MainScene(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}           //= constructor

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;
};

#endif //TESTGAME_MAINSCENE_H
