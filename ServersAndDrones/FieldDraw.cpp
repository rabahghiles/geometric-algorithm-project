//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "FieldDraw.h"


FieldDraw::FieldDraw(const string &title, int argc, char **argv, unsigned int width = 1000, unsigned int height = 856)
        : GlutWindow(argc, argv, title, width, height, FIXED){
    droneId=0;
    surfaceArea = width * height;
    firstTime = true;
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
    int i = 0;
    std::ofstream myfile;
    switch(c) {
        case 'z':
            if (!firstTime) {
                field->allPoints.clear();
                field->tabPts = nullptr;
                field->tabTriangles.clear();
                field->interiorPoints.clear();
                field->tabPolygons.clear();
                field->drones.clear();
                field->currentDrone = nullptr;

                field->convexHull();
                field->triangulation();
                field->getInteriorPoints();
                field->addInteriorPoints();
                field->checkDelaunay();
            }
            firstTime = false;

            field->delaunayTriangulation();
            field->checkDelaunay();

            field->voronoiDiagram(width,height);
            field->makePolygonTriangles();
            field->calculatePolygonAreas();
            break;
        case 's':
            myfile.open("../Data/servers.txt");
            for (auto s: field->servers) {
                if (i != field->servers.size()-1) {
                    myfile << s.city << ";(" << s.location->x << "," << s.location->y << ");" << s.color << '\n';
                }
                else {
                    myfile << s.city << ";(" << s.location->x << "," << s.location->y << ");" << s.color;
                }
                i++;
            }
            myfile.close();
            break;
        case 'd':
            field->addDrone();
            field->updateDesired(surfaceArea);
            field->transferDrone();
            break;
        case '1':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(RED);
                field->lastSelected.polygon->setSaveColor(RED);
            }
            break;
        case '2':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(ORANGE);
                field->lastSelected.polygon->setSaveColor(ORANGE);
            }
            break;
        case '3':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(YELLOW);
                field->lastSelected.polygon->setSaveColor(YELLOW);
            }
            break;
        case '4':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(GREEN);
                field->lastSelected.polygon->setSaveColor(GREEN);
            }
            break;
        case '5':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(CYAN);
                field->lastSelected.polygon->setSaveColor(CYAN);
            }
            break;
        case '6':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(BLUE);
                field->lastSelected.polygon->setSaveColor(BLUE);
            }
            break;
        case '7':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(PINK);
                field->lastSelected.polygon->setSaveColor(PINK);
            }
            break;
        case '8':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(PURPLE);
                field->lastSelected.polygon->setSaveColor(PURPLE);
            }
            break;
        case '9':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(MAGENTA);
                field->lastSelected.polygon->setSaveColor(MAGENTA);
            }
            break;
        case '0':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(GREY);
                field->lastSelected.polygon->setSaveColor(GREY);
            }
            break;
        case '-':
            if (field->lastSelected.city != "none") {
                field->lastSelected.polygon->setColor(BROWN);
                field->lastSelected.polygon->setSaveColor(BROWN);
            }
            break;
        case 127:
            field->servers.remove(field->lastSelected);
            break;
    }
}

void FieldDraw::onMouseMove(double cx, double cy) {
    Vector2D vertex((float)cx,(float)cy);
    field->onMouseMove(vertex);
}

void FieldDraw::onMouseDown(int button, double x, double y) {
    if (button == GLUT_LEFT_BUTTON) {
        field->findSelected(x,y);
    } else if (button == GLUT_RIGHT_BUTTON) {
        std::string name, color;

        std::cout << "Server City: ";
        std::cin >> name;
        std::cout << name << std::endl;

        std::cout << "Server Color: ";
        std::cin >> color;
        std::cout << color << std::endl;

        field->servers.push_back(Server(name,new Vector2D(x,y),color));
    }
}
