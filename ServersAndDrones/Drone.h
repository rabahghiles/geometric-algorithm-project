//
// Created by Kwabena Bamfo on 23/01/2020.
//

#ifndef SERVERSANDDRONES_DRONE_H
#define SERVERSANDDRONES_DRONE_H

#include <string>
#include "Vector2D.h"


class Drone {
private:
    int droneId;
    std::string icon;
    int width;
    int height;
    Vector2D *position;
    Vector2D *motion;
public:
    Drone();

    void draw();
    void move();
};


#endif //SERVERSANDDRONES_DRONE_H
