//
// Created by Kwabena Bamfo on 27/12/2019.
//
#include <iostream>
#include <fstream>
#include <sstream>

#include <glutWindow.h>
#include "Field.h"

Vector2D* getLocation(std::string location);
void flip(Triangle &ptr1, Triangle &ptr2);


Field::Field(std::string filename) {
    file = filename;
}

void Field::addServers() {
    std::string fileDir = "../Data/"+file;
    std::ifstream fin(fileDir);
    std::string line;

    while (std::getline(fin, line)) {
        int a = line.find(";");
        int b = line.find(";", a + 1);

        std::string city = line.substr(0, a);
        std::string location = line.substr(a + 1, b - (a + 1));
        Vector2D* loc = getLocation(location);
        std::string color = line.substr(b + 1, line.length() - (b + 1));

        servers.push_back(Server(city,loc,color));
    }
}

Vector2D* getLocation(std::string location){
    int comma = location.find(",");
    std::string locationx = location.substr(1,comma-1);
    std::string locationy = location.substr(comma+1,location.length()-(comma+2));

    std::stringstream x(locationx);
    float fx = 0;
    x >> fx;

    std::stringstream y(locationy);
    float fy = 0;
    y >> fy;

    Vector2D* vd = new Vector2D(fx,fy);

    return vd;
}

void Field::seeServers() {
    auto a = servers.begin();
    while (a != servers.end()) {
        std::cout << a->city << " " << a->location->x << "," << a->location->y << " " << a->color << std::endl;
        a++;
    }
}

bool Field::polarComparison(Vector2D P1, Vector2D P2) {
    double a1 = asin(P1.y / sqrt(P1.x * P1.x + P1.y * P1.y));
    if (P1.x < 0.0)
        a1 = M_PI - a1;

    double a2 = asin(P2.y / sqrt(P2.x * P2.x + P2.y * P2.y));
    if (P2.x < 0.0)
        a2 = M_PI - a2;

    return a1 < a2;
}

bool Field::isOnTheLeft(const Vector2D* P, const Vector2D* P1, const Vector2D* P2) {
    Vector2D AB = *P2 - *P1,
            AP = *P - *P1;
    return crossProduct(AB,AP) >= 0;
}

float Field::crossProduct(const Vector2D& u, const Vector2D& v) {
    return (u.x * v.y - u.y * v.x);
}

void Field::draw() {
    drawConvexHull();
    for (auto& triangle: tabTriangles) {
        triangle.draw();
    }

    for (auto& triangle: tabTriangles) {
        triangle.drawCircle();
    }
//    drawTriangulation();
}

void Field::convexHull() {
    auto ap = servers.begin();

    while (ap != servers.end()) {
        allPoints.push_back(ap->location);
        ap++;
    }

    auto s = servers.begin();
    auto symin = servers.begin();

    while(s != servers.end()) {
        if(s->location->y < symin->location->y) {
            symin = s;
        }
        s++;
    }

    // Swap
    if (symin != servers.begin())
        iter_swap(servers.begin(), symin);

    Vector2D origin{servers.begin()->location->x, servers.begin()->location->y};

    // Copy points in a set of points relative to points[0]
    std::vector<Vector2D> pointsRelative;
    for (auto pOrig: servers)
        pointsRelative.push_back(Vector2D{pOrig.location->x - origin.x, pOrig.location->y - origin.y});

    // Sorting point with angular criteria.
    sort(pointsRelative.begin() + 1, pointsRelative.end(), polarComparison);

    std::stack<Vector2D*> CHstack;
    Vector2D *top_1, *top;
    CHstack.push(&pointsRelative[0]);
    CHstack.push(&pointsRelative[1]);
    CHstack.push(&pointsRelative[2]);

    vector<Vector2D>::iterator pi = pointsRelative.begin() + 3;
    while (pi != pointsRelative.end()) {
        top = CHstack.top();
        CHstack.pop();
        top_1 = CHstack.top();
        CHstack.push(top);

        while (!isOnTheLeft(&(*pi), top_1, top)) {
            CHstack.pop();

            // Update values of top and top_1.
            top = CHstack.top();
            CHstack.pop();
            top_1 = CHstack.top();
            CHstack.push(top);
        }
        CHstack.push(&(*pi));
        pi++;
    }

    // Get stack points to create current polygon
    N = CHstack.size();
    Nmax = N;
    tabPts = new Vector2D[Nmax+1];

    int i = N-1;
    while (!CHstack.empty()) {
        tabPts[i--] = *(CHstack.top()) + origin;
        CHstack.pop();
    }
    tabPts[N] = tabPts[0];
}

void Field::drawConvexHull() {
    glColor3fv(BLACK);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<N; i++) {
        glVertex2f(tabPts[i].x, tabPts[i].y);
    }
    glEnd();

    glLineWidth(1);
    for (int i=0; i<N; i++) {
        glBegin(GL_LINES);
        glVertex2f(tabPts[i].x - 10, tabPts[i].y - 10);
        glVertex2f(tabPts[i].x + 10, tabPts[i].y + 10);
        glEnd();

        glBegin(GL_LINES);
        glVertex2f(tabPts[i].x + 10, tabPts[i].y - 10);
        glVertex2f(tabPts[i].x - 10, tabPts[i].y + 10);
        glEnd();

        GlutWindow::drawText(tabPts[i].x - 10, tabPts[i].y, to_string(i), GlutWindow::ALIGN_RIGHT);
    }

    // plot all points (for convex hull)
    for (Vector2D* points: allPoints) {
        glColor3fv(RED);
        GlutWindow::fillEllipse(points->x, points->y, 2.5, 2.5);
    }
}

void Field::triangulation() {
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
        tabTriangles.push_back(T);
        tmp.erase(p+1); // remove point(p + 1) from tmp.
        n--; // or n = tmp.size().
    }
}

void Field::drawTriangulation() {
    glColor3fv(WHITE);
    glBegin(GL_TRIANGLES);
    for (auto t: tabTriangles) {
        glVertex2f(t.ptr[0]->x, t.ptr[0]->y);
        glVertex2f(t.ptr[1]->x, t.ptr[1]->y);
        glVertex2f(t.ptr[2]->x, t.ptr[2]->y);
    }
    glEnd();

    glColor3fv(BLACK);
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);

    // draw border using triangles
    for (auto t: tabTriangles) {
        glVertex2f(t.ptr[0]->x, t.ptr[0]->y);
        glVertex2f(t.ptr[1]->x, t.ptr[1]->y);
        glVertex2f(t.ptr[2]->x, t.ptr[2]->y);
    }
    glEnd();
}

void Field::getInteriorPoints() {
    auto p = allPoints.begin();

    while (p != allPoints.end()) {
        bool isInterior = true;
        for(int i=0; i<N && isInterior; i++) {
            if((*p)->x == tabPts[i].x && (*p)->y == tabPts[i].y)
                isInterior = false;
        }
        if(isInterior)
            interiorPoints.push_back(*p);
        p++;
    }
}

void Field::seeInteriorPoints() {
    for(auto p: interiorPoints) {
        std::cout << p->x << "," << p->y << std::endl;
    }
}

void Field::addInteriorPoints() {
    std::list<Triangle*> processList;

    auto t = tabTriangles.begin();
    // copy tabTriangles in a list
    while (t != tabTriangles.end()) {
        processList.push_back(&(*t));
        t++;
    }

    auto pl = processList.begin();
    bool test;

    while(pl != processList.end()) {
        Triangle *current = *pl;
        Vector2D *a = current->ptr[0];
        Vector2D *b = current->ptr[1];
        Vector2D *c = current->ptr[2];

        auto ip = interiorPoints.begin();
        while(ip != interiorPoints.end()) {
            test = current->isInside(*(*ip));
            if (test) {
                tabTriangles.remove(*current);
                tabTriangles.push_back(Triangle(a,b,*ip));
                tabTriangles.push_back(Triangle(b,c,*ip));
                tabTriangles.push_back(Triangle(c,a,*ip));
            }
            ip++;
        }
        pl++;
    }
//    std::cout << tabTriangles.size() << std::endl;
}

void Field::delaunayTriangulation() {
    std::list<Triangle*> processList;
    auto t = tabTriangles.begin();

    // copy tabTriangles in a list
    while (t != tabTriangles.end()) {
        processList.push_back(&(*t));
        t++;
    }

    // while a triangle is in the list
    while (processList.size()>1) {
        Triangle *current = processList.front(); // pop current
        processList.pop_front();

        // if current is not Delaunay
        if (!current->isDelaunay) {
//            std::cout << "current: " << current->ptr[0]->x << "," << current->ptr[0]->y;
//            std::cout << " " << current->ptr[1]->x << "," << current->ptr[1]->y;
//            std::cout << " " << current->ptr[2]->x << "," << current->ptr[2]->y << std::endl;
            Triangle *Tneighbor = neighborInside(current);
//            std::cout << "neighbour found: " << Tneighbor->ptr[0]->x << "," << Tneighbor->ptr[0]->y;
//            std::cout << " " << Tneighbor->ptr[1]->x << "," << Tneighbor->ptr[1]->y;
//            std::cout << " " << Tneighbor->ptr[2]->x << "," << Tneighbor->ptr[2]->y << std::endl;

            // and if a neighbor is available
            if (Tneighbor!=nullptr) {
                flip(*current,*Tneighbor); // flip the common edge

                // remove Tneighbor from the list
                auto tr=processList.begin();
                while (tr!=processList.end() && (*tr)!=Tneighbor) {
                    tr++;
                }
                if (tr!=processList.end()) processList.erase(tr);
            } else {
                processList.push_back(current); // postpone the treatment
            }
        }
    }
}

Triangle* Field::neighborInside(Triangle* currentTriangle) {
    Vector2D* a = currentTriangle->ptr[0];
    Vector2D* b = currentTriangle->ptr[1];
    Vector2D* c = currentTriangle->ptr[2];

    auto t = tabTriangles.begin();
    while (t != tabTriangles.end()) {
        // check if there exists a triangle with a vector inside currentTriangle
        if (currentTriangle->isInsideCircle(*t->ptr[0]) ||
            currentTriangle->isInsideCircle(*t->ptr[1]) ||
            currentTriangle->isInsideCircle(*t->ptr[2])) {

            bool a_foundMatch = false, b_foundMatch = false, c_foundMatch = false;

            for(int i=0; i<3; i++){
                if (!a_foundMatch && a->x==t->ptr[i]->x && a->y==t->ptr[i]->y)
                    a_foundMatch = true;
                if (!b_foundMatch && b->x==t->ptr[i]->x && b->y==t->ptr[i]->y)
                    b_foundMatch = true;
                if (!c_foundMatch && c->x==t->ptr[i]->x && c->y==t->ptr[i]->y)
                    c_foundMatch = true;
            }

            // check if there exists a common edge (i.e there exists two similar points)
            if( (a_foundMatch && b_foundMatch) ||
                (a_foundMatch && c_foundMatch) ||
                (b_foundMatch && c_foundMatch) ) {

                return &(*t);
            }
        }
        t++;
    }
    return nullptr;
}

void flip(Triangle &ptr1, Triangle &ptr2) {
    // search common edge
    Vector2D *P = ptr1.getVertexNotIn(ptr2);
    Vector2D *Q = ptr2.getVertexNotIn(ptr1);
    Vector2D *R = ptr1.getNextVertex(P);
    Vector2D *S = ptr2.getNextVertex(Q);

    ptr1.updateVertices(P,R,Q);
    ptr2.updateVertices(Q,S,P);
}

void Field::onMouseMove(const Vector2D& pos) {
    for (auto& triangle: tabTriangles) {
        triangle.onMouseMove(pos);
    }
}

void Field::checkDelaunay() {
    auto t = tabTriangles.begin();
    while (t != tabTriangles.end()) {
        t->checkDelaunay(allPoints);
        t++;
    }
}




