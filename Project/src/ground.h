//
// Created by Brecht on 22/01/2019.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_GROUND_H
#define GBA_SPRITE_ENGINE_PROJECT_GROUND_H

#include <vector>
#include <utility>

class Ground {
private:
    std::vector<std::pair<int,int>> coordinates;
public:
    Ground(){};
    Ground(int param[][2], int size);
    void getClosestCoordinates(std::pair<int, int> coordinate, std::pair<int, int>& leftCoordinate, std::pair<int, int>& rightCoordinate);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_GROUND_H
