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

//const float WHITE[4]={1.0, 1.0, 1.0, 1.0f};
//const float BLACK[4]={0.0, 0.0, 0.0, 1.0f};
//const float GREY[4]={0.75f, 0.75f, 0.75f, 1.0f};
//const float RED[4]={1.0f, 0.0, 0.0, 1.0f};
//const float ORANGE[4]={1.0f, 0.27f, 0.0, 1.0f};
//const float YELLOW[4]={1.0f, 1.0f, 0.0, 1.0f};
//const float GREEN[4]={0.0, 1.0f, 0.0, 1.0f};
//const float BLUE[4]={0.0, 0.0, 1.0f, 1.0f};


class Server {
public:
    std::string city;
    Vector2D* location;
    std::string color;
//    float color[4];
    Polygon* polygon;

    Server(){

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
