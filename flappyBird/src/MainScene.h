//
// Created by Jolien Jeunen on 27/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MAINSCENE_H
#define GBA_SPRITE_ENGINE_PROJECT_MAINSCENE_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/background/background.h>

class MainScene : public Scene {
private:
    std::unique_ptr<Background> bg;
    std::unique_ptr<AffineSprite> birdSprite;
    std::unique_ptr<AffineSprite> buisSprite;
    std::unique_ptr<AffineSprite> buisSprite1;
    std::unique_ptr<AffineSprite> buisSprite2;

    int scrollX, scrollY;
    double birdX;
    double birdY;
    int score,highScore;


    void youDied();
    void resetGame();

public:
    MainScene(std::shared_ptr<GBAEngine> engine) : Scene(engine)/*, birdX(0), birdY(0), scrollX(0), scrollY(0)*/ {}

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    void load() override;
    void tick(u16 keys) override;          //i = keys
};

#endif //GBA_SPRITE_ENGINE_PROJECT_MAINSCENE_H
