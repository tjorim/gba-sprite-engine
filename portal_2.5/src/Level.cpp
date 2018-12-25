//
// Created by Leander on 21/12/2018.
//

#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Level.h"
#include "GameOverScene.h"


const std::unique_ptr<Chell> &Level::getChell() const { return chell; }

const std::unique_ptr<Portal> &Level::getRedPortal() const { return redPortal; }

const std::unique_ptr<Portal> &Level::getBluePortal() const { return bluePortal; }

const std::unique_ptr<Visier> &Level::getVisier() const { return visier; }

const std::unique_ptr<Portal_bullet> &Level::getRedBullet() const { return redBullet; }

const std::unique_ptr<Portal_bullet> &Level::getBlueBullet() const { return blueBullet; }

const std::vector<std::unique_ptr<WallTile>> &Level::getVerticalPortalWallVec() const { return verticalPortalWallVec; }

const std::vector<std::unique_ptr<WallTile>> &Level::getVerticalWallVec() const { return verticalWallVec; }

const std::vector<std::unique_ptr<WallTile>> &Level::getHorizontalPortalWallVec() const { return horizontalPortalWallVec; }

const std::vector<std::unique_ptr<WallTile>> &Level::getHorizontalWallVec() const { return horizontalWallVec; }

const std::unique_ptr<Button> &Level::getButton() const { return button; }

void Level::moveChell(bool leftKey, bool rightKey, bool jump) {
    VECTOR vec = {0,0,0};
    if (leftKey == true){ vec.x = -1; }
    if (rightKey == true){ vec.x = 1; }
    if (jump == true){
        chell->doJump();
    }

    vec.y = chell->controleJump();
    vec = verticalCollisionDetect(chell.get(), verticalPortalWallVec, vec);
    vec = verticalCollisionDetect(chell.get(), verticalWallVec, vec);
    vec = horizontalCollisionDetect(chell.get(), horizontalPortalWallVec, vec);
    vec =horizontalCollisionDetect(chell.get(), horizontalWallVec,vec);

    chell->setXSnelheid(vec.x);
    chell->setYSnelheid(vec.y);
    visier->setXSnelheid(vec.x);
    visier->setYSnelheid(vec.y);
}

VECTOR Level::verticalCollisionDetect(Chell* player, std::vector<std::unique_ptr<WallTile>> &walls, VECTOR vec) {
    for(auto& s : walls) {
        if (player->getSprite()->collidesWith(*s->getSprite())){
            if (player->getXCoordinaat() < s->getXCoordinaat()){
                if (vec.x > 0) { return  {0, vec.y}; }
            }
            if (player->getXCoordinaat() > s->getXCoordinaat()){
                if (vec.x < 0) { return {0, vec.y}; }
            }
        }
    }
    return vec;
}

VECTOR Level::horizontalCollisionDetect(Chell* player, std::vector<std::unique_ptr<WallTile>> &walls, VECTOR vec) {
    for(auto& s : walls) {
        if (player->getSprite()->collidesWith(*s->getSprite())){
            if ( player->getYCoordinaat() < s->getYCoordinaat()){
                if (vec.y > 0) { return {vec.x, 0}; }
            }
            if (player->getYCoordinaat() > s->getYCoordinaat()){
                if (vec.y < 0) { return {vec.x, 0}; }
            }
        }
    }
    return vec;
}

void Level::shoot(Portal_bullet *bullet){
    if (bullet->getIsMoving() == false) {
        bullet->setx(visier->getXCoordinaat() + 28);
        bullet->sety(visier->getYCoordinaat() + 28);
        bullet->setDestination(visier->getPc(), visier->getXCoordinaat(), visier->getYCoordinaat(), visier->getSprite()->getWidth());
        bullet->start(visier->getFlipVisier(), bullet->getx(), bullet->gety());
        bullet->setIsMoving(true);
    }
}

void Level::update(){
    redBullet->tick();
    blueBullet->tick();

    bulletCollisionWall(redBullet.get(), verticalWallVec);
    bulletCollisionWall(blueBullet.get(), verticalWallVec);
    bulletCollisionWall(redBullet.get(), horizontalWallVec);
    bulletCollisionWall(blueBullet.get(), horizontalWallVec);

    bulletCollisionPortalWall(redBullet.get(), redPortal.get(), verticalPortalWallVec);
    bulletCollisionPortalWall(redBullet.get(), redPortal.get(), horizontalPortalWallVec);
    bulletCollisionPortalWall(blueBullet.get(), bluePortal.get(), verticalPortalWallVec);
    bulletCollisionPortalWall(blueBullet.get(), bluePortal.get(), horizontalPortalWallVec);

    updateTiles(verticalPortalWallVec);
    updateTiles(horizontalPortalWallVec);
}

void Level::bulletCollisionWall(Portal_bullet* bullet, std::vector<std::unique_ptr<WallTile>> &walls){
    for(auto& s : walls) {
        if (bullet->getSprite()->collidesWith(*s->getSprite())) {
            bullet->setIsMoving(false);
        }
    }
}

void Level::bulletCollisionPortalWall(Portal_bullet* bullet, Portal* portal, std::vector<std::unique_ptr<WallTile>> &walls){
    for(auto& s : walls) {
        if (bullet->getSprite()->collidesWith(*s->getSprite())) {
            removePortal(verticalPortalWallVec, portal);
            removePortal(horizontalPortalWallVec, portal);
            s->setHasPortal(true);
            bullet->setIsMoving(false);
            if (walls == horizontalPortalWallVec){
                portal->setPortal(true, s->getXCoordinaat(), s->getYCoordinaat());
                portal->setDirection(getDirection(portal, horizontalWallVec));
            }
            if (walls == verticalPortalWallVec){
                portal->setPortal(false, s->getXCoordinaat(), s->getYCoordinaat());
                portal->setDirection(getDirection(portal, verticalWallVec));
            }
        }
    }
}

void Level::removePortal(std::vector<std::unique_ptr<WallTile>> &walls, Portal* portal){
    for(auto& s : walls) {
        if ((s->getHasPortal()==true) && (s->getXCoordinaat()!= portal->getXCoordinaat() && s->getYCoordinaat()!=portal->getYCoordinaat())){}
        else{s->setHasPortal(false);};
    }
}

void Level::updateTiles(std::vector<std::unique_ptr<WallTile>> &walls) {
    for(auto& s : walls) {
        s->updateView();
    }
}

void Level::checkPortals(){
    portalCollision(chell.get(), bluePortal.get(), redPortal->getHorizontalSprite(), visier.get());
    portalCollision(chell.get(), redPortal.get(), bluePortal->getHorizontalSprite(), visier.get());

    portalCollision(chell.get(), bluePortal.get(), redPortal->getVerticalSprite(), visier.get());
    portalCollision(chell.get(), redPortal.get(), bluePortal->getVerticalSprite(), visier.get());
}

bool Level::getDirection(Portal* portal, std::vector<std::unique_ptr<WallTile>> &walls){
    for(auto& s : walls) {
        if (portal->getOrientation()==true) {
           if ((s->getYCoordinaat() == portal->getYCoordinaat() - 8)) {
                return true;
            }
        }
        if ((s->getXCoordinaat() == portal->getXCoordinaat() - 8)) {
            return true;
        }
    }
    return false;
}


void Level::portalCollision(Chell* player, Portal* portalOut, Sprite* sprite, Visier* visier){
    if(player->getSprite()->collidesWith(*sprite)){
        if (portalOut->getOrientation() == true){
            if(portalOut->getDirection() == true){
                player->setLocation(portalOut->getXCoordinaat()+8, portalOut->getYCoordinaat()+8);
                visier->setLocation(portalOut->getXCoordinaat()+8-24, portalOut->getYCoordinaat()+8-24);
            }else{
                player->setLocation(portalOut->getXCoordinaat()+8, portalOut->getYCoordinaat()-32);
                visier->setLocation(portalOut->getXCoordinaat()+8-24, portalOut->getYCoordinaat()-32-24);
            }
        }
        else {
            if(portalOut->getDirection() == true){
                player->setLocation(portalOut->getXCoordinaat()+8, portalOut->getYCoordinaat());
                visier->setLocation(portalOut->getXCoordinaat()+8-24, portalOut->getYCoordinaat()-24);
            }else{
                player->setLocation(portalOut->getXCoordinaat()-16, portalOut->getYCoordinaat());
                visier->setLocation(portalOut->getXCoordinaat()-16-24, portalOut->getYCoordinaat()-24);
            }
        }
    }
}


