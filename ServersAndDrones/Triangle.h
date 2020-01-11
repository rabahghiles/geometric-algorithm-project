//
// Created by Kwabena Bamfo on 27/12/2019.
//

#ifndef SERVERSANDDRONES_TRIANGLE_H
#define SERVERSANDDRONES_TRIANGLE_H

#include "Vector2D.h"
#include "determinant.h"
#include <vector>

#include "Server.h"

//const float WHITE[4]={1.0, 1.0, 1.0, 1.0f};
//const float BLACK[4]={0.0, 0.0, 0.0, 1.0f};
//const float GREY[4]={0.75f, 0.75f, 0.75f, 1.0f};
//const float RED[4]={1.0f, 0.0, 0.0, 1.0f};
//const float ORANGE[4]={1.0f, 0.27f, 0.0, 1.0f};
//const float YELLOW[4]={1.0f, 1.0f, 0.0, 1.0f};
//const float GREEN[4]={0.0, 1.0f, 0.0, 1.0f};
//const float BLUE[4]={0.0, 0.0, 1.0f, 1.0f};

class Triangle {
public:
    Vector2D* ptr[3];
    bool isHighlighted;
    Vector2D circumCenter;
    float circumRadius;
    bool isDelaunay;

    Triangle(Vector2D* ptr1, Vector2D* ptr2, Vector2D* ptr3);

    bool isOnTheLeft(const Vector2D* p, const Vector2D* p1, const Vector2D* p2);
    float crossProduct(const Vector2D& u, const Vector2D& v);
    bool isEmpty(const std::vector<Vector2D*> &tmp, int n);
    bool isInside(const Vector2D& p);
    void updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3);
    bool operator == (const Triangle& t) const;
    Vector2D* getVertexNotIn(Triangle triangle);
    Vector2D* getNextVertex(Vector2D *vector);
    bool isInsideCircle(const Vector2D &P);
    void calculateCircle();
    bool checkDelaunay(const std::vector<Vector2D*> &points);
    void onMouseMove(const Vector2D& pos);
    void draw();
    void drawCircle();

    };


#endif //SERVERSANDDRONES_TRIANGLE_H
