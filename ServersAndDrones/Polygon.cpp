//
// Created by Kwabena Bamfo on 12/01/2020.
//

#include "Polygon.h"

Polygon::Polygon(int p_max) : tabPts{new Vector2D[p_max]}, Nmax{p_max}, N{0} {
    setColor(YELLOW);
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
    wmemcpy(reinterpret_cast<wchar_t *>(color), reinterpret_cast<const wchar_t *>(t_color), 4 * sizeof(float));
}

float Polygon::crossProduct(const Vector2D& u, const Vector2D& v) {
    return (u.x * v.y - u.y * v.x);
}

void Polygon::draw() {

    // Draw the interior of the polygon.
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < N; i++) {
        glVertex2f(tabPts[i].x, tabPts[i].y);
    }
    glEnd();

    // Draw the borders of the polygon.
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < N; i++)
    {
        glVertex2f(tabPts[i].x, tabPts[i].y);
    }
    glEnd();
}
