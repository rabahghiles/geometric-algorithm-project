//
// Created by Kwabena Bamfo on 12/01/2020.
//

#ifndef SERVERSANDDRONES_POLYGON_H
#define SERVERSANDDRONES_POLYGON_H

#include <glutWindow.h>

#include "Vector2D.h"
#include "Triangle.h"


class Polygon {
    Vector2D *tabPts;
    int Nmax;
    float color[4];

public:
    int N;
    Polygon(int p_max);
    ~Polygon();

    bool addVector(const Vector2D &p);
    void draw();

    /**
     * @brief Check if the vertex p is inside the polygon.
     * @param p the vertex to check.
     * @return true if the vertex p is inside, false otherwise.
     */
    bool isInside(const Vector2D& p);

    /**
    * @brief Test if the vertex is on the left of the vertex p.
    * @param p
    * @param i
    * @return true if the vertex is on the left, false otherwise
    */
    bool isOnTheLeft(const Vector2D& p, int i);

    /**
    * @brief check if the polygon is convex.
    * @return true if the polygon is convex, false otherwise.
    */
    bool isConvex();

    void triangulation();
    static bool polarComparison(Vector2D P1, Vector2D P2);
    bool isOnTheLeft(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);
    float crossProduct(const Vector2D& u, const Vector2D& v);
    void setColor(const float *t_color);
};


#endif //SERVERSANDDRONES_POLYGON_H
