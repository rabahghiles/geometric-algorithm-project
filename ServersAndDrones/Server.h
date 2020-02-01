//
// Created by Kwabena Bamfo on 27/12/2019.
//

#ifndef SERVERSANDDRONES_SERVER_H
#define SERVERSANDDRONES_SERVER_H

#include <iostream>

#include <string>
#include <sstream>
#include "Vector2D.h"
#include "Polygon.h"
class Drone;

class Server {
public:
    GLuint serverId;
    std::vector<Drone*> drones;
    int nbrDrone;
    std::string city;
    Vector2D* location;
    std::string color;
    Polygon* polygon;

    Server(){
        //Drone draw
        int lx, ly;
        serverId = GlutWindow::loadTGATexture("../Images/server512x512.tga", lx, ly);
        assert(serverId != 0);
        city = "none";
    }

    Server(std::string sCity, Vector2D* sLocation, std::string sColor){
        //Drone draw
        int lx, ly;
        serverId = GlutWindow::loadTGATexture("../Images/server512x512.tga", lx, ly);
        assert(serverId != 0);

        city = sCity;
        location = sLocation;
        color = sColor;
    }

    void draw();
    bool operator == (const Server& s) const;

};


#endif //SERVERSANDDRONES_SERVER_H
