#include <iostream>

#include "FieldDraw.h"

int main(int argc, char **argv) {
    FieldDraw fd = FieldDraw("Servers And Drones World", argc, argv, 1000, 856);
    fd.start();

    return 0;
}

Vector2D operator*(float a,const Vector2D &v) {
    return Vector2D(a*v.x,a*v.y);
}