//
// Created by 桂明谦 on 2019/12/19.
//

#ifndef FARTRACE_MMATH_HPP
#define FARTRACE_MMATH_HPP

extern "C"{
#include "mmath.h"
};

class Vector2D{
public:
    Vector2D();
    Vector2D(const Vector vec);
    Vector2D(float x, float y);
    Vector2D(Pointf p1, Pointf p2);
    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
    float operator*(const Vector2D& other);
    Vector2D operator/(const Vector2D& other);
    float operator^(const Vector2D& other);
    void operator=(const Vector2D& other);
    bool operator==(const Vector2D& other);
    Vector2D operator+=(const Vector2D& other);
    Vector2D operator-=(const Vector2D& other);
    float operator*=(const Vector2D& other);
    Vector2D operator/=(const Vector2D& other);
    float operator^=(const Vector2D& other);
    float GetLen() const;
    void Rotate(float angle);
    float Dot(const Vector2D& other) const;
    float Cross(const Vector2D& other) const;
    Vector GetVector();
    float GetX() const;
    float GetY() const;
    void SetVector(float nx, float ny);
    void SetX(float nx);
    void SetY(float ny);
    void Normalize();
private:
    Vector v;
};

Vector2D Normalize(const Vector2D& v);
Vector2D Rotate(const Vector2D& v, float angle);
#endif //FARTRACE_MMATH_HPP
