#include <iostream>

#include "FieldDraw.h"

int main(int argc, char **argv) {
    FieldDraw fd{"Servers And Drones World", argc, argv, 1000, 1000};
    fd.start();

    return 0;
}

Vector2D operator*(float a,const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}