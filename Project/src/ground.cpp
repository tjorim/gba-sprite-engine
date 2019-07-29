//
// Created by Brecht on 22/01/2019.
//

#include "ground.h"

Ground::Ground(int param[][2], int size){
    for(int i = 0; i < size; i++){
        coordinates.emplace_back(std::make_pair(param[i][0], param[i][1]));
    }
}

void Ground::getClosestCoordinates(std::pair<int, int> coordinate, std::pair<int, int> &leftCoordinate,
                                   std::pair<int, int> &rightCoordinate) {
    leftCoordinate = std::make_pair(0, 160);
    rightCoordinate = std::make_pair(240, 160);

    int x = coordinate.first;

    int size = coordinates.size();
    for(int i = 0; i < size; i++){
        int coordinateX = coordinates.at(i).first;

        if(coordinateX <= x && coordinateX >= leftCoordinate.first){
            leftCoordinate = coordinates.at(i);
        }

        if(coordinateX >= x && coordinateX <= rightCoordinate.first){
            rightCoordinate = coordinates.at(i);
        }
    }
}