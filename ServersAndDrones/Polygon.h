//
// Created by Kwabena Bamfo on 12/01/2020.
//

#ifndef SERVERSANDDRONES_POLYGON_H
#define SERVERSANDDRONES_POLYGON_H

#include <glutWindow.h>

#include "Vector2D.h"
#include "Triangle.h"


class Polygon {
    std::vector<Triangle> polyTriangles;
    int Nmax;

public:
    int N;
    Polygon(int p_max);
    ~Polygon();

    float surfaceArea;
    Vector2D *tabPts;

    float currentDrones;
    float desiredDrones;
    float showDrones;

    float color[4];
    float saveColor[4];
    bool isSelected;

    bool addVector(const Vector2D &p);
    void draw();
    void calculateArea();
    void updateDesired(float fieldArea, int totalDrones);

    /**
     * @brief Check if the vertex p is inside the polygon.
     * @param p the vertex to check.
     * @return true if the vertex p is inside, false otherwise.
     */
    bool isInside(const Vector2D &p);

    /**
    * @brief Test if the vertex is on the left of the vertex p.
    * @param p
    * @param i
    * @return true if the vertex is on the left, false otherwise
    */
    bool isOnTheLeft(const Vector2D &p, int i);

    void triangulation();
    float crossProduct(const Vector2D &u, const Vector2D &v);

    void setColor(const float *t_color);
    void setSaveColor(const float *t_color);

    bool isInsideRight(const Vector2D &p);
    bool isInsideLeft(const Vector2D &p);
    bool isOnTheRight(const Vector2D &p, int i);

};


#endif //SERVERSANDDRONES_POLYGON_H
