//
// Created by gadegbe on 20/01/2020.
//

#ifndef SERVERSANDDRONES_DRONE_H
#define SERVERSANDDRONES_DRONE_H


#include <iostream>
#include <string>
#include <glutWindow.h>
#include <vector>
#include <vector>

#include "Server.h"

class Drone {

private:
    GLuint droneId;
    Vector2D* speed;
    Vector2D* location;
    Vector2D* acceleration;
    Vector2D* start;
    Server* server;
    float weight;
    float radius;
    float maxSpeed;
    double dmax;
    double r;
    float thrustForceStrength;
    float collisionForceStrength;
    float smoothDamping;

public:

    Drone();

    void draw(std::vector<Drone *> drones);

    void updateServer(Server *newServer);

    Vector2D getPosition();

    void updateSpeed(std::vector<Drone *> drones);

};


#endif //SERVERSANDDRONES_DRONE_H
