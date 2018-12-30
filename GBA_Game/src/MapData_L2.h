//
// Created by Wout Briels on 30/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_MAPDATA_L2_H
#define GBA_SPRITE_ENGINE_PROJECT_MAPDATA_L2_H

class MapData_L2 {
private:
    int groundY;
    int topY;
    bool movePermissionL;
    bool movePermissionR;

public:
    void createGroundLevel(int playerX, int playerY) {
        // Layer 2
        if (playerY < 112) {
            switch (playerX) {
                case 0 ... 63 :
                    groundY = 96;
                    break;
                case 73 ... 111 :
                    groundY = 96;
                    break;
                case 129 ... 160 :
                    groundY = 104;
                    break;
                case 161 ... 176 :
                    groundY = 88;
                    break;
                case 177 ... 223 :
                    groundY = 72;
                    break;
                case 224 ... 256 :
                    groundY = 88;
                    break;
                default:
                    groundY = 300;
                    break;
            }
        }
        // Layer 1
        else {
            if (playerY < 192 && playerX < 144) {
                switch (playerX) {
                    case 49 ... 143 :
                        groundY = 184;
                        break;
                    default:
                        groundY = 300;
                        break;
                }
            } else {
                switch (playerX) {
                    case 0 ... 31 :
                        groundY = 240;
                        break;
                    case 41 ... 152 :
                        groundY = 240;
                        break;
                    case 153 ... 168 :
                        groundY = 224;
                        break;
                    case 169 ... 184 :
                        groundY = 208;
                        break;
                    case 185 ... 200 :
                        groundY = 192;
                        break;
                    case 201 ... 256 :
                        groundY = 176;
                        break;
                    default:
                        groundY = 300;
                        break;
                }
            }
        }
    }

    int getGroundLevel() {
        return  groundY;
    }

    void createTopLevel(int playerX, int playerY) {
        if (playerY >= 136 && playerY < 192) {
            switch (playerX) {
                case 8 ... 63 :
                    topY = 144;
                    break;
                case 73 ... 111 :
                    topY = 144;
                    break;
                default:
                    topY = 0;
                    break;
            }
        } else if (playerY >= 192) {
            switch (playerX) {
                case 49 ... 143 :
                    topY = 200;
                    break;
                default:
                    topY = 0;
                    break;
            }
        } else {
            topY = 0;
        }
    }

    int getTopLevel() {
        return topY;
    }

    void createBarrierL(int playerX, int playerY) {
        if (playerX == 0) {
            movePermissionL = false;
        } else if (playerX == 8 && playerY >= 144) {
            movePermissionL = false;
        } else {
            // Layer 2
            if (playerX != 0 && playerY < 176) {
                if (playerX == 64 && playerY >= 96) {
                    movePermissionL = false;
                } else if (playerX == 112 && playerY >= 96) {
                    movePermissionL = false;
                } else if (playerX == 224 && playerY >= 72 && playerY < 89) {
                    movePermissionL = false;
                } else {
                    movePermissionL = true;
                }
            }
            // Layer 1
            else {  // playerY <= 176
                if (playerX == 32 && playerY >= 240) {
                    movePermissionL = false;
                } else if (playerX == 144 && playerY >= 184 && playerY < 232) {
                    movePermissionL = false;
                } else {
                    movePermissionL = true;
                }
            }
        }

    }

    bool getMovePermissionL() {
        return movePermissionL;
    }

    void createBarrierR(int playerX, int playerY) {
        if (playerX == 240) {
            movePermissionR = false;
        } else {
            // Layer 2
            if (playerX != 240 && playerY < 176) {
                if (playerX == 72 && playerY >= 96) {
                    movePermissionR = false;
                } else if (playerX == 128 && playerY >= 104 && playerY < 151) {
                    movePermissionR = false;
                } else if (playerX == 160 && playerY >= 88 && playerY < 135) {
                    movePermissionR = false;
                } else if (playerX == 176 && playerY >= 72 && playerY < 119) {
                    movePermissionR = false;
                } else {
                    movePermissionR = true;
                }
            }
            // Layer 1
            else {
                if (playerX == 40 && playerY >= 240) {
                    movePermissionR = false;
                } else if (playerX == 48 && playerY >= 184 && playerY < 232) {
                    movePermissionR = false;
                } else if (playerX == 152 && playerY >= 224) {
                    movePermissionR = false;
                } else if (playerX == 168 && playerY >= 208) {
                    movePermissionR = false;
                } else if (playerX == 184 && playerY >= 192) {
                    movePermissionR = false;
                } else if (playerX == 200 && playerY >= 176) {
                    movePermissionR = false;
                } else {
                    movePermissionR = true;
                }
            }
        }
    }

    bool getMovePermissionR() {
        return movePermissionR;
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_MAPDATA_L2_H
