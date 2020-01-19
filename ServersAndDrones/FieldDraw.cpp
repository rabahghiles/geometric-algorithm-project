//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "FieldDraw.h"


FieldDraw::FieldDraw(const string &title, int argc, char **argv, unsigned int width = 1000, unsigned int height = 1000)
        : GlutWindow(argc, argv, title, width, height, FIXED){

}

void FieldDraw::onStart() {
    std::cout << "Start.." << std::endl;
    field = new Field();
    field->addServers();
//    field->seeServers();
    field->convexHull();
    field->triangulation();
    field->getInteriorPoints();
//    field->seeInteriorPoints();
    field->addInteriorPoints();
    field->checkDelaunay();
    glClearColor(1.0, 1.0, 1.0, 1.0);

}

void FieldDraw::onDraw() {
    field->draw();
}

void FieldDraw::onQuit() {

}

void FieldDraw::onKeyPressed(unsigned char c, double x, double y) {
    switch(c) {
        case 's':
            field->delaunayTriangulation();
            field->checkDelaunay();
            break;
        case 'v':
            field->voronoiDiagram();
    }
}

void FieldDraw::onMouseMove(double cx, double cy) {
    Vector2D vertex((float)cx,(float)cy);
//    for (auto t:tris) {
//        t->onMouseMove(v);
//    }

    field->onMouseMove(vertex);
}
