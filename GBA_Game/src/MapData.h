//
// Created by Wout Briels on 18/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H


class GroundLevel {
private:
    int groundY;

public:
    void createGroundLevel(int groundX) {
        switch (groundX) {
            case 0 ... 47 :         // Tile coor 0 - 40
                groundY = 176;
                break;
            case 48 ... 64 :        // Tile coor 48 - 56      // (64)
                groundY = 240;

            // HOLE                         // Tile coor 64 - 72

            case 65 ... 112 :       // Tile coor 80 - 120
                groundY = 240;
                break;
            case 113 ... 128 :       // Tile coor 128 - 136
                groundY = 224;
                break;
            case 129 ... 144 :       // Tile coor 144 - 152
                groundY = 208;
                break;
            case 145 ... 160 :       // Tile coor 160 - 168
                groundY = 192;
                break;
            case 161 ... 200 :       // Tile coor 176 - 192
                groundY = 176;
                break;

            // HOLE                         // Tile coor 200 - 208

            case 201 ... 240 :       // Tile coor 216 - 248
                groundY = 176;
                break;
            default :
                groundY = 256;
                break;
        }
    }

    int getGroundLevel() {
        return  groundY;
    }

    void setToGroundLevel(int playerX, int playerY) {
        playerY = groundY + 32;
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H
