//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "Triangle.h"
#include <glutWindow.h>

Triangle::Triangle() {
    Vector2D* sentinel = new Vector2D(-1,-1);
    ptr[0] = sentinel;
    ptr[1] = sentinel;
    ptr[2] = sentinel;
    isHighlighted = false;
    calculateCircle();
}

Triangle::Triangle(Vector2D* ptr1, Vector2D* ptr2, Vector2D* ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
    isHighlighted = false;
    calculateCircle();
}

bool Triangle::isOnTheLeft(const Vector2D* p, const Vector2D* p1, const Vector2D* p2) {
    Vector2D ab = *p2 - *p1,
            ap = *p - *p1;

    return crossProduct(ab,ap) >= 0;
}

bool Triangle::isEmpty(const std::vector<Vector2D*> &tmp, int n) {
    auto p = tmp.begin() + n;
    while(p != tmp.end() && !isInside(*(*p)))
        p++;

    return p == tmp.end();
}

bool Triangle::isInside(const Vector2D& p) {
    return isOnTheLeft(&p, ptr[0], ptr[1]) &&
           isOnTheLeft(&p, ptr[1], ptr[2]) &&
           isOnTheLeft(&p, ptr[2], ptr[0]);
}

float Triangle::crossProduct(const Vector2D& u, const Vector2D& v) {
    return (u.x*v.y - u.y*v.x);
}

void Triangle::updateVertices(Vector2D *ptr1,Vector2D *ptr2,Vector2D *ptr3) {
    ptr[0] = ptr1;
    ptr[1] = ptr2;
    ptr[2] = ptr3;
    isHighlighted = false;
    calculateCircle();
}

bool Triangle::operator==(const Triangle &t) const {
    bool equal = true;
    for(int i=0; i<3; i++) {
        if ((t.ptr[i]->x == ptr[0]->x && t.ptr[i]->y == ptr[0]->y) ||
            (t.ptr[i]->x == ptr[1]->x && t.ptr[i]->y == ptr[1]->y) ||
            (t.ptr[i]->x == ptr[2]->x && t.ptr[i]->y == ptr[2]->y)) {
            // do nothing
        } else {
            equal = false;
        }
    }
    return equal;
}

bool Triangle::operator!=(const Triangle &t) const {
    bool equal = true;
    for(int i=0; i<3; i++) {
        if ((t.ptr[i]->x == ptr[0]->x && t.ptr[i]->y == ptr[0]->y) ||
            (t.ptr[i]->x == ptr[1]->x && t.ptr[i]->y == ptr[1]->y) ||
            (t.ptr[i]->x == ptr[2]->x && t.ptr[i]->y == ptr[2]->y)) {
            // do nothing
        } else {
            equal = false;
        }
    }
    return !equal;
}

Vector2D* Triangle::getVertexNotIn(Triangle triangle) {
    bool a,b,c,d,e,f;
    for(int i=0; i<3; i++) {
        a = ptr[i]->x != triangle.ptr[0]->x;
        b = ptr[i]->y != triangle.ptr[0]->y;

        c = ptr[i]->x != triangle.ptr[1]->x;
        d = ptr[i]->y != triangle.ptr[1]->y;

        e = ptr[i]->x != triangle.ptr[2]->x;
        f = ptr[i]->y != triangle.ptr[2]->y;

        if(a && b && c && d && e && f)
            return ptr[i];
    }
}

Vector2D* Triangle::getNextVertex(Vector2D *vector) {
    for(int i=0; i<3; i++) {
        bool a = ptr[i]->x == vector->x && ptr[i]->y == vector->y;
        if(a) {
            i++;
            return (ptr[i%3]);
        }
    }
}

Vector2D *Triangle::getPrevVertex(Vector2D *vector) {
    for(int i=0; i<3; i++) {
        bool a = ptr[i]->x == vector->x && ptr[i]->y == vector->y;
        if(a) {
            i--;
            if(i==-1)
                return (ptr[2]);
            else
                return (ptr[i]);
        }
    }
}

bool Triangle::isInsideCircle(const Vector2D &P) {
    Matrix33 mat33;

    mat33.m[0][0] = ptr[0]->x - P.x;
    mat33.m[0][1] = ptr[0]->y - P.y;
    mat33.m[0][2] = ((ptr[0]->x * ptr[0]->x) - (P.x * P.x)) + ((ptr[0])->y * ptr[0]->y) - (P.y * P.y);

    mat33.m[1][0] = ptr[1]->x - P.x;
    mat33.m[1][1] = ptr[1]->y - P.y;
    mat33.m[1][2] = ((ptr[1]->x * ptr[1]->x) - (P.x * P.x)) + ((ptr[1]->y * ptr[1]->y) - (P.y * P.y));

    mat33.m[2][0] = ptr[2]->x - P.x;
    mat33.m[2][1] = ptr[2]->y - P.y;
    mat33.m[2][2] = ((ptr[2]->x * ptr[2]->x) - (P.x * P.x)) + ((ptr[2]->y * ptr[2]->y) - (P.y * P.y));

    return mat33.determinant() > 0;
}

void Triangle::calculateCircle() {
    // calculate circle parameters
    // AB = B - A
    Vector2D AB = *ptr[1] - *ptr[0];
    Vector2D AC = *ptr[2] - *ptr[0];
    Vector2D VAC = AC.ortho();
    float k = (AB * AB - AC * AB) / (2 * (VAC * AB));

    circumCenter = 0.5f * AC + (k*VAC) + *ptr[0]; // O + 0.5AC + k * VAC + A
    circumRadius = (circumCenter - *ptr[0]).norm(); // R = AO = BO = CO
}

void Triangle::onMouseMove(const Vector2D& pos) {
    isHighlighted = isInside(pos);
}

bool Triangle::checkDelaunay(const std::vector<Vector2D*> &points) {
    auto p = points.begin();
    while(p != points.end() && !isInsideCircle(*(*p))) {
        p++;
    }
    isDelaunay = p == points.end();
    return isDelaunay;
}

void Triangle::draw() {
    glColor3fv(isDelaunay ? (isHighlighted ? GREEN : GREY) : (isHighlighted ? ORANGE : YELLOW));

    // Draw the triangle.
    glBegin(GL_TRIANGLES);
    glVertex2f(ptr[0]->x,ptr[0]->y);
    glVertex2f(ptr[1]->x,ptr[1]->y);
    glVertex2f(ptr[2]->x,ptr[2]->y);
    glEnd();

    // Draw the borders.
    glColor3fv(BLACK);
    glBegin(GL_LINE_LOOP);
    glVertex2f(ptr[0]->x,ptr[0]->y);
    glVertex2f(ptr[1]->x,ptr[1]->y);
    glVertex2f(ptr[2]->x,ptr[2]->y);
    glEnd();
}

void Triangle::drawCircle() {
    // draw circle
    if (isHighlighted) {
        glColor3fv(RED);
        glPushMatrix();
        glTranslatef(circumCenter.x, circumCenter.y, 0);
        glLineWidth(3);
        glBegin(GL_LINE_LOOP);
        float a=0.0;
        for (int i=0; i<40; i++) {
            glVertex2f(circumRadius * cos(a), circumRadius * sin(a));
            a+=(float)(M_PI/20.0);
        }
        glEnd();
        glLineWidth(1);
        glPopMatrix();
    }
}

bool Triangle::hasAsVertex(Vector2D *vector) {
    for(int i=0; i<3; i++) {
        if(ptr[i]->x == vector->x && ptr[i]->y == vector->y)
            return true;
    }
    return false;
}

Triangle Triangle::getRightNeighbour(std::list<Triangle> triSubset) {
    for(auto triangle: triSubset){
        if(*this != triangle) {
            Vector2D *a = triangle.ptr[0];
            Vector2D *b = triangle.ptr[1];
            Vector2D *c = triangle.ptr[2];

            bool a_foundMatch = false, b_foundMatch = false, c_foundMatch = false;

            for (int i = 0; i < 3; i++) {
                if (!a_foundMatch && a->x == ptr[i]->x && a->y == ptr[i]->y)
                    a_foundMatch = true;
                if (!b_foundMatch && b->x == ptr[i]->x && b->y == ptr[i]->y)
                    b_foundMatch = true;
                if (!c_foundMatch && c->x == ptr[i]->x && c->y == ptr[i]->y)
                    c_foundMatch = true;
            }

            if( (a_foundMatch && b_foundMatch) ||
                (a_foundMatch && c_foundMatch) ||
                (b_foundMatch && c_foundMatch) ) {

                return triangle;
            }
        }
    }
    return Triangle();
//    Vector2D* sentinel = new Vector2D(-1,-1);
//    return Triangle(sentinel,sentinel,sentinel);
}
