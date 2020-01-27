//
// Created by Kwabena Bamfo on 12/01/2020.
//

#include <cstring>
#include "Polygon.h"

Polygon::Polygon(int p_max) : tabPts{new Vector2D[p_max]}, Nmax{p_max}, N{0} {
    setColor(WHITE);
    setSelectColor(WHITE);
    setSaveColor(WHITE);
    c = "WHITE";
    selectC = "WHITE";
    saveC = "WHITE";
    surfaceArea = 0;
    currentDrones = 0;
    desiredDrones = 0;
    isHighlighted = false;
}

Polygon::~Polygon() {
    delete [] tabPts;
}

bool Polygon::addVector(const Vector2D &p) {
    if(N == Nmax) return false;

    tabPts[N++] = p;
    tabPts[N] = tabPts[0];
    return true;
}

void Polygon::setColor(const float *t_color) {
    memcpy(color, t_color, 4 * sizeof(float));
}

void Polygon::setSelectColor(const float *t_color) {
    memcpy(selectColor, t_color, 4 * sizeof(float));
}

void Polygon::setSaveColor(const float *t_color) {
    memcpy(saveColor, t_color, 4 * sizeof(float));
}

float Polygon::crossProduct(const Vector2D& u, const Vector2D& v) {
    return (u.x * v.y - u.y * v.x);
}

void Polygon::draw() {

    // Draw the interior of the polygon.
//    glColor3fv(color);
    glColor3fv((color));

//    glBegin(GL_POLYGON);
//    for (int i = 0; i < N; i++) {
//        glVertex2f(tabPts[i].x, tabPts[i].y);
//    }
//    glEnd();
//
//    // Draw the borders of the polygon.
//    glColor3f(0,0,0);
//    glBegin(GL_LINE_LOOP);
//        for (int i = 0; i < N; i++)
//    {
//        glVertex2f(tabPts[i].x, tabPts[i].y);
//    }
//    glEnd();

    glBegin(GL_TRIANGLES);
    for (auto t: polyTriangles) {
        glVertex2f(t.ptr[0]->x, t.ptr[0]->y);
        glVertex2f(t.ptr[1]->x, t.ptr[1]->y);
        glVertex2f(t.ptr[2]->x, t.ptr[2]->y);
    }
    glEnd();

    // Draw the border
    glColor3fv(BLACK);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);

    // draw border using triangles
//    for (auto t: polyTriangles) {
//        glVertex2f(t.ptr[0]->x, t.ptr[0]->y);
//        glVertex2f(t.ptr[1]->x, t.ptr[1]->y);
//        glVertex2f(t.ptr[2]->x, t.ptr[2]->y);
//    }
//    glEnd();

    // draw border by linking line
    for (int i = 0; i < N; i++) {
        glVertex2f(tabPts[i].x, tabPts[i].y);
    }
    glEnd();
}

void Polygon::triangulation() {
    std::vector<Vector2D*> tmp;

    // copy the list of vertices in the tmp list.
    for (int i=0; i<N; i++) {
        tmp.push_back(&(tabPts[i]));
    }

    int n = N;

    // while we can add a triangle to tabTriangle.
    while (n>2) {
        int i = 0;
        auto p = tmp.begin();
        bool test;
        // create a triangle using p, p+1 and p+2 as vertices
        Triangle T(*p,*(p+1),*(p+2));

        // Search a triangle without another points inside
        do {
            test = !T.isEmpty(tmp, i+3);
            if (test) {
                i++;
                p++;
                T = Triangle(*p,*(p+1),*(p+2));
            }
        } while (i<n-2 && test);

        assert(i<n-2);

        // Add T to tabTriangles.
        polyTriangles.push_back(T);
        tmp.erase(p+1); // remove point(p + 1) from tmp.
        n--; // or n = tmp.size().
    }
}

void Polygon::calculateArea() {
    for(auto p: polyTriangles) {
        Vector2D AB = *p.ptr[1] - *p.ptr[0];
        Vector2D BC = *p.ptr[2] - *p.ptr[1];
        Vector2D CA = *p.ptr[0] - *p.ptr[2];

        double a = AB.norm();
        double b = BC.norm();
        double c = CA.norm();

        auto s = (a + b + c) / 2;
        auto calculated = std::sqrt(s * (s-a) * (s-b) * (s-c));
        std::cout << calculated << std::endl;
        surfaceArea += calculated;
    }
    std::cout << "Final Area: " << surfaceArea << std::endl;
}

void Polygon::updateDesired(float fieldArea, int totalDrones) {
    std::cout << std::endl;
    std::cout << "Equation : (" << totalDrones << "*" << surfaceArea << ") / (" << fieldArea << ")" << std::endl;
    desiredDrones = totalDrones * surfaceArea / 856232;
    std::cout << "Desired drones: " << desiredDrones << std::endl;
    desiredDrones = desiredDrones - currentDrones;
    std::cout << "Actual desired drones: " << desiredDrones << std::endl;
    std::cout << std::endl;
}

//bool Polygon::isInside(const Vector2D &p) {
//    int i = 0;
//    while (i<N && isOnTheLeft(p,i)) {
//        i++;
//    }
//    std::cout << "i: " << i << " N:" << N << std::endl;
//    return i == N;
//}
//
//bool Polygon::isOnTheLeft(const Vector2D &p, int i) {
//    Vector2D u = tabPts[i+1] - tabPts[i],
//            v = p - tabPts[i];
//    return crossProduct(u,v) >= 0;
//}
//
//bool Polygon::isOnTheLeft(const Vector2D *p, const Vector2D *p1, const Vector2D *p2) {
//    Vector2D AB = *p2 - *p1,
//            AP = *p - *p1;
//    return crossProduct(AB,AP) >= 0;
//}

bool Polygon::isInside(const Vector2D &p) {

    return isInsideLeft(p) || isInsideRight(p);
}

bool Polygon::isInsideLeft(const Vector2D &p) {
    int i = 0;
    while (i < N && isOnTheLeft(p, i)) {
        i++;
    }
//    cout << " * " << endl;
//    std::cout << "i: " << i << " N:" << N << std::endl;
    return i == N;
}

bool Polygon::isInsideRight(const Vector2D &p) {
    int i = 0;
    while (i < N && isOnTheRight(p, i)) {
        i++;
    }
//    cout << " * " << endl;
//    std::cout << "i: " << i << " N:" << N << std::endl;
    return i == N;
}

bool Polygon::isOnTheLeft(const Vector2D &p, int i) {
    Vector2D u = tabPts[i + 1] - tabPts[i],
            v = p - tabPts[i];

    return crossProduct(u, v) >= 0;
}

bool Polygon::isOnTheRight(const Vector2D &p, int i) {
    Vector2D u = tabPts[i + 1] - tabPts[i],
            v = p - tabPts[i];

    return crossProduct(u, v) <= 0;
}

void Polygon::onMouseMove(const Vector2D& pos) {
    isHighlighted = isInside(pos);
}
