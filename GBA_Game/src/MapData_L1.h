//
// Created by Wout Briels on 18/12/2018.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H
#define GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H


class MapData_L1 {
    /**
     * All coordinates in this class are the coordinates of the
     * parameters in a 256x256 map (not GBA_screen map).
     */
private:
    int groundY;
    int topY;
    int coinX, coinY;
    bool movePermissionL, movePermissionR;

public:
    void createGroundLevel(int playerX, int playerY) {
        // Layer 1
        if (playerY > 120) {
            switch (playerX) {
                case 0 ... 47 :         // Tile coor 0 - 40
                    groundY = 176;
                    break;
                case 48 ... 63 :        // Tile coor 48 - 56      // (64)
                    groundY = 240;

                    // HOLE                         // Tile coor 64 - 80

                case 73 ... 112 :       // Tile coor 88 - 120
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
                case 161 ... 256 :
                    if (playerY < 208) {            // Could also be a switch case statement!!
                        switch (playerX) {
                            case 161 ... 199 :       // Tile coor 176 - 192
                                groundY = 176;
                                break;

                                // HOLE                         // Tile coor 200 - 216

                            case 209 ... 240 :       // Tile coor 224 - 248
                                groundY = 176;
                                break;
                            default :
                                groundY = 300;
                                break;
                        }
                    } else {
                        switch (playerX) {
                            case 176 ... 183 :       // Tile coor 176 - 184
                                groundY = 240;
                                break;

                                // HOLE                         // Tile coor 184 - 200

                            case 193 ... 224 :       // Tile coor 208 - 248
                                groundY = 240;
                                break;
                            default :
                                groundY = 300;
                                break;
                        }
                    }
                    break;
                default:
                    groundY = 300;
                    break;
            }
        }
        // Layer 2
        else {
            switch (playerX) {
                case 224 ... 255:
                    groundY = 96;
                    break;
                case 200 ... 223:
                    groundY = 88;
                    break;
                case 176 ... 199:
                    groundY = 80;
                    break;
                case 137 ... 175:
                    groundY = 72;
                    break;
                case 96 ... 127:
                    groundY = 80;
                    break;
                case 80 ... 95:
                    groundY = 72;
                    break;
                case 16 ... 79:
                    groundY = 64;
                    break;
                default:
                    groundY = 255;
            }
        }
    }

    int getGroundLevel() {
        return  groundY;
    }

    void createTopLevel(int playerX, int playerY) {
        // Layer 1
        if (playerY > 200) {
            switch (playerX) {
                case 176 ... 199 :
                    topY = 208;
                    break;
                case 209 ... 224 :
                    topY = 208;
                    break;
                default:
                    topY = 0;
                    break;
            }
        }
        // Layer 2
        else if (playerY < 64) {
            switch (playerX) {
                case 16 :
                    topY = 16;
                    break;
                case 17 ... 55 :
                    topY = 32;
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
        } else {

            // Layer 1
            if (playerX != 0 && playerY > 136) {
                if (playerX == 48 && playerY >= 176) {
                    movePermissionL = false;
                } else if (playerX == 64 && playerY >= 240) {
                    movePermissionL = false;
                } else if (playerX == 176 && playerY >= 208) {
                    movePermissionL = false;
                } else if (playerX == 184 && playerY >= 240) {
                    movePermissionL = false;
                } else if (playerX == 200 && playerY >= 176 && playerY < 239) {
                    movePermissionL = false;
                } else {
                    movePermissionL = true;
                }
            }
            // Layer 2
            else {  // playerY <= 96
                if (playerX == 224 && playerY >= 88) {
                    movePermissionL = false;
                } else if (playerX == 200 && playerY >= 80) {
                    movePermissionL = false;
                } else if (playerX == 176 && playerY >= 72) {
                    movePermissionL = false;
                } else if (playerX == 128 && playerY >= 80 && playerY < 127) {
                    movePermissionL = false;
                } else if (playerX == 96 && playerY >= 72 && playerY < 127) {
                    movePermissionL = false;
                } else if (playerX == 80 && playerY >= 64 && playerY < 127) {
                    movePermissionL = false;
                } else if (playerX == 56 && playerY < 63) {
                    movePermissionL = false;
                } else if (playerX == 16 && playerY < 95) {
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
            // Layer 1
            if (playerX != 240 && playerY > 136) {
                if (playerX == 72 && playerY >= 240) {
                    movePermissionR = false;
                } else if (playerX == 112 && playerY >= 224) {
                    movePermissionR = false;
                } else if (playerX == 128 && playerY >= 208) {
                    movePermissionR = false;
                } else if (playerX == 144 && playerY >= 192) {
                    movePermissionR = false;
                } else if (playerX == 160 && playerY >= 176) {
                    movePermissionR = false;
                } else if (playerX == 192 && playerY >= 240) {
                    movePermissionR = false;
                } else if (playerX == 208 && playerY >= 176 && playerY < 239) {
                    movePermissionR = false;
                } else if (playerX == 224 && playerY >= 208) {
                    movePermissionR = false;
                } else {
                    movePermissionR = true;
                }
            }
            // Layer 2
            else {
                if (playerX == 136 && playerY >= 72 && playerY < 119) {
                    movePermissionR = false;
                } else if (playerX == 16 && playerY < 64) {
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

    void setCoinPositionX (int coinNr) {
        if (coinNr == 1) {
            coinX = 56;
        } else if (coinNr == 2) {
            coinX = 240;
        } else if (coinNr == 3) {
            coinX = 224;
        } else if (coinNr == 4) {
            coinX = 184;
        } else if (coinNr == 5) {
            coinX = 64;
        } else if (coinNr == 6) {   // When no more coins.
            coinX = 300; // Move coin out of map.
        }
    }

    int getCoinPositionX() {
        return coinX;
    }

    void setCoinPositionY (int coinNr) {
        if (coinNr == 1) {
            coinY = 232;
        } else if (coinNr == 2) {
            coinY = 168;
        } else if (coinNr == 3) {
            coinY = 232;
        } else if (coinNr == 4) {
            coinY = 72;
        } else if (coinNr == 5) {
            coinY = 56;
        } else if (coinNr == 6) {   // When no more coins.
            coinY = 300; // Move coin out of map.
        }
    }

    int getCoinPositionY() {
        return coinY;
    }
};

#endif //GBA_SPRITE_ENGINE_PROJECT_GROUNDLEVEL_H