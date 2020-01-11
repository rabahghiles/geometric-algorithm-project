//
// Created by Kwabena Bamfo on 27/12/2019.
//

#ifndef SERVERSANDDRONES_VECTOR2D_H
#define SERVERSANDDRONES_VECTOR2D_H

#include <cmath>


class Vector2D {
public:
    float x, y;

    Vector2D();
    Vector2D(const Vector2D &v);
    Vector2D(float x, float y);

    Vector2D operator-(const Vector2D &vector2D) const;
    Vector2D operator+(const Vector2D &vector2D) const;

    float operator*(const Vector2D &op2) const {
        return x*op2.x+y*op2.y;
    }

    void set(float p_x,float p_y) {
        x=p_x;
        y=p_y;
    }

    void normalize() {
        float norm= std::sqrt(x*x+y*y);
        x/=norm;
        y/=norm;
    }

    double norm() {
        return std::sqrt(x*x+y*y);
    }

    Vector2D ortho() {
        return Vector2D(-y,x);
    }
};

Vector2D operator*(float a,const Vector2D &v);
//{
//    return Vector2D(a*v.x,a*v.y);
//}


#endif //SERVERSANDDRONES_VECTOR2D_H
