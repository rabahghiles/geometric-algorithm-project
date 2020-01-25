//
// Created by gadegbe on 20/01/2020.
//

#ifndef SERVERSANDDRONES_DRONE_H
#define SERVERSANDDRONES_DRONE_H


#include <iostream>
#include <string>
#include <glutWindow.h>
#include <vector>

#include "Server.h"

class Drone {

private:
    GLuint droneId;
    Vector2D* speed;
    Vector2D* location;
    Vector2D* acceleration;
    Server* server;

public:

    Drone();

    void draw(vector<Drone> drones);

    void updateServer(Server *newServer);

    void updateSpeed(vector<Drone> drones);
};


#endif //SERVERSANDDRONES_DRONE_H
