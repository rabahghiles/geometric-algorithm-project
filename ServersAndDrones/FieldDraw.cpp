//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "FieldDraw.h"


FieldDraw::FieldDraw(const string &title, int argc, char **argv, unsigned int width = 1000, unsigned int height = 856)
        : GlutWindow(argc, argv, title, width, height, FIXED){
    droneId=0;
    surfaceArea = width * height;
    Server* selectedServer;
    Polygon* selectedPolygon;
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void FieldDraw::onDraw() {
    field->draw();
}

void FieldDraw::onQuit() {
    glDeleteTextures(1,&droneId);
}

void FieldDraw::onKeyPressed(unsigned char c, double x, double y) {
    switch(c) {
        case 's':
            field->delaunayTriangulation();
            field->checkDelaunay();
            break;
        case 'v':
            field->voronoiDiagram(width,height);
            field->makePolygonTriangles();
            field->calculatePolygonAreas();
//            for(auto s: field->servers) {
//                std::cout << s.city << ":" << s.polygon->surfaceArea << std::endl;
//            }
            break;
        case 'd':
            field->addDrone();
            field->updateDesired(surfaceArea);
            field->transferDrone();
            break;
        case '1':
            if(field->lastSelected.polygon->c == "WHITE") {
                field->lastSelected.polygon->setColor(RED);
                field->lastSelected.polygon->setSaveColor(RED);
                field->lastSelected.polygon->c = "RED";
                field->lastSelected.polygon->saveC = "RED";
            }
            break;
        case '2':
            field->lastSelected.polygon->setColor(ORANGE);
            field->lastSelected.polygon->setSaveColor(ORANGE);
            field->lastSelected.polygon->c = "ORANGE";
            field->lastSelected.polygon->saveC = "ORANGE";
            break;
        case '3':
            field->lastSelected.polygon->setColor(YELLOW);
            field->lastSelected.polygon->setSaveColor(YELLOW);
            field->lastSelected.polygon->c = "YELLOW";
            field->lastSelected.polygon->saveC = "YELLOW";
            break;
        case '4':
            field->lastSelected.polygon->setColor(GREEN);
            field->lastSelected.polygon->setSaveColor(GREEN);
            field->lastSelected.polygon->c = "GREEN";
            field->lastSelected.polygon->saveC = "GREEN";
            break;
        case '5':
            field->lastSelected.polygon->setColor(CYAN);
            field->lastSelected.polygon->setSaveColor(CYAN);
            field->lastSelected.polygon->c = "CYAN";
            field->lastSelected.polygon->saveC = "CYAN";
            break;
        case '6':
            field->lastSelected.polygon->setColor(BLUE);
            field->lastSelected.polygon->setSaveColor(BLUE);
            field->lastSelected.polygon->c = "BLUE";
            field->lastSelected.polygon->saveC = "BLUE";
            break;
        case '7':
            field->lastSelected.polygon->setColor(PINK);
            field->lastSelected.polygon->setSaveColor(PINK);
            field->lastSelected.polygon->c = "PINK";
            field->lastSelected.polygon->saveC = "PINK";
            break;
        case '8':
            field->lastSelected.polygon->setColor(PURPLE);
            field->lastSelected.polygon->setSaveColor(PURPLE);
            field->lastSelected.polygon->c = "PURPLE";
            field->lastSelected.polygon->saveC = "PURPLE";
            break;
        case '9':
            field->lastSelected.polygon->setColor(MAGENTA);
            field->lastSelected.polygon->setSaveColor(MAGENTA);
            field->lastSelected.polygon->c = "MAGENTA";
            field->lastSelected.polygon->saveC = "MAGENTA";
            break;
        case '0':
            field->lastSelected.polygon->setColor(GREY);
            field->lastSelected.polygon->setSaveColor(GREY);
            field->lastSelected.polygon->c = "GREY";
            field->lastSelected.polygon->saveC = "GREY";
            break;
        case '-':
            field->lastSelected.polygon->setColor(BROWN);
            field->lastSelected.polygon->setSaveColor(BROWN);
            field->lastSelected.polygon->c = "BROWN";
            field->lastSelected.polygon->saveC = "BROWN";
            break;
    }
}

void FieldDraw::onMouseMove(double cx, double cy) {
    Vector2D vertex((float)cx,(float)cy);
//    for (auto t:tris) {
//        t->onMouseMove(v);
//    }

    field->onMouseMove(vertex);
}

void FieldDraw::onMouseDown(int button, double x, double y) {
    if (button = GLUT_RIGHT_BUTTON) {
        field->findSelected(x,y);
    }
}
