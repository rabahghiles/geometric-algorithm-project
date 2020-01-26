//
// Created by Kwabena Bamfo on 23/01/2020.
//

#ifndef SERVERSANDDRONES_DRONE_H
#define SERVERSANDDRONES_DRONE_H

#include <string>
#include "Vector2D.h"
#include "Server.h"


class Drone {
private:
    int droneId;
    std::string icon;
    int width;
    int height;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D target;

public:
    Vector2D position;

    Drone();

    void draw();
    void move();
    void updateServer(Server server);
};


#endif //SERVERSANDDRONES_DRONE_H
