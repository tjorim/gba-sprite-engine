//
// Created by Leander on 21/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVEL_H


#include <algorithm>
#include <vector>
#include "Chell.h"
#include "WallTile.h"
#include "Portal.h"
#include "Visier.h"
#include "Portal_bullet.h"


class Level {

private:
    std::unique_ptr<Chell> chell;
    std::unique_ptr<Portal> redPortal, bluePortal;
    std::unique_ptr<Visier> visier;
    std::unique_ptr<Portal_bullet> redBullet, blueBullet;
    std::vector<std::unique_ptr<WallTile>> verticalPortalWallVec, verticalWallVec, horizontalPortalWallVec, horizontalWallVec;

public:
    Level(std::unique_ptr<Chell> chellObject, std::vector<std::unique_ptr<WallTile>> verticalPortalWallVecObject,  std::vector<std::unique_ptr<WallTile>> verticalWallVecObject,
          std::vector<std::unique_ptr<WallTile>> horizontalPortalWallVecObject,  std::vector<std::unique_ptr<WallTile>> horizontalWallVecObject, std::unique_ptr<Portal> redPortalObject,
          std::unique_ptr<Portal> bluePortalObject, std::unique_ptr<Visier> visierObject, std::unique_ptr<Portal_bullet> redBulletObject, std::unique_ptr<Portal_bullet> blueBulletObject) : chell(std::move(chellObject)),
          verticalPortalWallVec(std::move(verticalPortalWallVecObject)), verticalWallVec(std::move(verticalWallVecObject)),horizontalPortalWallVec(std::move(horizontalPortalWallVecObject)),
          horizontalWallVec(std::move(horizontalWallVecObject)), redPortal(std::move(redPortalObject)), bluePortal(std::move(bluePortalObject)), visier(std::move(visierObject)),
          redBullet(std::move(redBulletObject)), blueBullet(std::move(blueBulletObject)){};

    Level(){}

    const std::unique_ptr<Chell> &getChell() const;
    const std::unique_ptr<Portal> &getRedPortal() const;
    const std::unique_ptr<Portal> &getBluePortal() const;
    const std::unique_ptr<Visier> &getVisier() const;
    const std::unique_ptr<Portal_bullet> &getRedBullet() const;
    const std::unique_ptr<Portal_bullet> &getBlueBullet() const;
    const std::vector<std::unique_ptr<WallTile>> &getVerticalPortalWallVec() const;
    const std::vector<std::unique_ptr<WallTile>> &getVerticalWallVec() const;
    const std::vector<std::unique_ptr<WallTile>> &getHorizontalPortalWallVec() const;
    const std::vector<std::unique_ptr<WallTile>> &getHorizontalWallVec() const;;

    void moveChell(bool leftKey, bool rightKey, bool jump);
    VECTOR verticalCollisionDetect(Chell* player, std::vector<std::unique_ptr<WallTile>> &walls, VECTOR vec);
    VECTOR horizontalCollisionDetect(Chell* player, std::vector<std::unique_ptr<WallTile>> &walls, VECTOR vec);
    void turnVisier(bool richting);
    void shoot(Portal_bullet *bullet);
    void update();
    void bulletCollisionWall(Portal_bullet* bullet, std::vector<std::unique_ptr<WallTile>> &walls);
    void bulletCollisionPortalWall(Portal_bullet* bullet, Portal* portal, std::vector<std::unique_ptr<WallTile>> &walls);
    void updatePortals();
    void updateTiles(std::vector<std::unique_ptr<WallTile>> &walls);
    void removePortal(std::vector<std::unique_ptr<WallTile>> &walls, Portal* portal);
    void checkPortals();
    void portalCollision(Chell* player, Portal* portalOut, Sprite* portalInSprite, Visier* visier);
    bool getDirection(Portal* portal, std::vector<std::unique_ptr<WallTile>> &walls);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_LEVEL_H
