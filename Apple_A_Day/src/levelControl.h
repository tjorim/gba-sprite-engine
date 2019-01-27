//
// Created by lloyd on 09-Jan-19.
//

#include "Direction.h"
//#include "mapMatrix.h"
#include "type.h"

#ifndef GBA_SPRITE_ENGINE_PROJECT_LEVELCONTROL_H
#define GBA_SPRITE_ENGINE_PROJECT_LEVELCONTROL_H


class levelControl {

private:

    Type level1[16][16]= {{Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,}};


    Type level2[16][16]= {{Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO,},
                          {Type::NOGO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::NOGO, Type::NOGO, Type::GO, Type::NOGO, Type::NOGO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::NOGO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO, Type::NOGO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,},
                          {Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::NOGO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO, Type::GO,}};




public:

    bool isNextTileGo(int playerX, int playerY, int scrollX, int scrollY, Direction currentDir, int currentLvl) {
        int centerX;
        int centerY;
        int restX;
        int restY;
        int volgendeX = 0;
        int volgendeY = 0;
        int checkX;
        int checkY;

        centerX = (playerX + 16 + scrollX);
        centerY = (playerY + 16 + scrollY);

        restX = (centerX) % 16;
        restY = (centerY) % 16;


        switch (currentDir) {
            case Direction::LEFT : {
                checkX = centerX;
                restX = (checkX) % 16;
                if ((restX > -1) && (restX < 6) ) {
                    volgendeX = (centerX - 16) / 16;
                    volgendeY = centerY / 16;
                }
                break;
            }
            case Direction::RIGHT : {
                checkX = centerX;
                restX = (checkX) % 16;
                if ((restX > 9) && (restX < 16)) {
                    volgendeX = ((centerX + 16) / 16);
                    volgendeY = centerY / 16;
                }
                break;
            }
            case Direction::UP : {
                checkY = centerY;
                restY = (checkY) % 16;
                if ((restY > -1) && (restY < 6)) {
                    volgendeY = (centerY - 16) / 16;
                    volgendeX = centerX / 16;
                }
                break;
            }
            case Direction::DOWN : {
                checkY = centerY;
                restY = (checkY) % 16;
                if ((restY > 9) && (restY < 16)) {
                    volgendeY = (centerY + 16) / 16;
                    volgendeX = centerX / 16;
                }
                break;
            }
        }
        switch (currentLvl) {
            case 1 : {
                if (level1[volgendeY][volgendeX] == Type::NOGO) {
                    return false;
                }
                break;
            }
            case 2 : {
                if (level2[volgendeY][volgendeX] == Type::NOGO) {
                    return false;
                }
                break;
            }
        }

        return true;
    }

};

#endif //GBA_SPRITE_ENGINE_PROJECT_LEVELCONTROL_H
