//
// Created by Kwabena Bamfo on 27/12/2019.
//

#include "Vector2D.h"


Vector2D::Vector2D() : x{0}, y{0}{}

Vector2D::Vector2D(float x, float y) : x{x}, y{y}{}

Vector2D::Vector2D(const Vector2D &v) : x{v.x}, y{v.y} {}

Vector2D Vector2D::operator-(const Vector2D &op2) const {
    return Vector2D(x - op2.x, y - op2.y);
}

Vector2D Vector2D::operator+(const Vector2D &op2) const{
    return Vector2D(x + op2.x, y + op2.y);
}
