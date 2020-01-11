//
// Created by Kwabena Bamfo on 27/12/2019.
//

#ifndef SERVERSANDDRONES_FIELD_H
#define SERVERSANDDRONES_FIELD_H


#include "Server.h"
#include "Triangle.h"

#include <list>
#include <vector>

class Field {
    std::string file;
    int numServers;
    std::vector<Server> servers;

    int N;
    int Nmax;
    Vector2D *tabPts;
    std::vector<Vector2D*> allPoints;
    std::vector<Vector2D*> interiorPoints;


public:
    std::list<Triangle> tabTriangles;
    Field(std::string filename = "servers.txt");

    void addServers();
    void seeServers();
    void convexHull();
    void triangulation();
    void draw();
    void drawConvexHull();
    void drawTriangulation();
    void getInteriorPoints();
    void seeInteriorPoints();
    void addInteriorPoints();
    void delaunayTriangulation();


    static bool polarComparison(Vector2D P1, Vector2D P2);
    bool isOnTheLeft(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);
    float crossProduct(const Vector2D& u, const Vector2D& v);
    Triangle* neighborInside(Triangle* currentTriangle);
    void onMouseMove(const Vector2D& pos);
    void checkDelaunay();


    };


#endif //SERVERSANDDRONES_FIELD_H