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

class Server {
public:
    std::string city;
    Vector2D* location;
    std::string color;
//    float color[4];
    Polygon* polygon;

    Server(){
        city = "none";
    }

    Server(std::string sCity, Vector2D* sLocation, std::string sColor){
        city = sCity;
        location = sLocation;
        color = sColor;
//        setColor(RED);
    }

//    void setColor(const float *t_color);
};


#endif //SERVERSANDDRONES_SERVER_H
