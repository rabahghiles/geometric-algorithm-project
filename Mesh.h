
#ifndef GEOMETRY_TRIANGULATION_GL_MESH_H
#define GEOMETRY_TRIANGULATION_GL_MESH_H

#include <vector>
#include "Triangle.h"

class Mesh {
public:
    vector<Vector2D> vertices;
    vector<Triangle> triangles;

    Mesh(vector<Vector2D> &p_vert);
    Mesh(const float p_vert[][2], int p_nvert,const int p_tri[][3],int p_ntri);

    void draw();
    void onMouseMove(double x,double y);
    bool checkDelaunay();
    const Triangle *getTriangle(const Vector2D &pt) const;
    Triangle *neighborInside(const Triangle *T);
    Triangle *findTriangle(const Vector2D *P1,const Vector2D *P2);
    void flip(Triangle &ptr1,Triangle &ptr2);
    void solveDelaunay();
    void subdivide(const Vector2D &P);
};

#endif //GEOMETRY_TRIANGULATION_GL_MESH_H
