//
// Created by 桂明谦 on 2019/12/21.
//

#include "engin/mmath.hpp"

Vector2D::Vector2D():v({0, 0}){}

Vector2D::Vector2D(float x, float y):v({x, y}){}

Vector2D::Vector2D(Pointf p1, Pointf p2):v({p2.x-p1.x, p2.y-p1.y}){}

Vector2D::Vector2D(const Vector vec):v({vec.x, vec.y}){}

float Vector2D::GetX() const{
    return v.x;
}

float Vector2D::GetY() const{
    return v.y;
}

void Vector2D::SetVector(float nx, float ny){
    v.x = nx;
    v.y = ny;
}

void Vector2D::SetX(float nx){
    v.x = nx;
}

void Vector2D::SetY(float ny){
    v.y = ny;
}

Vector2D Vector2D::operator+(const Vector2D& other){
    return Vec_Add(&v, &other.v);
}

Vector2D Vector2D::operator-(const Vector2D& other){
    return Vec_Sub(&v, &other.v);
}

float Vector2D::operator*(const Vector2D& other){
    return Dot(other);
}

Vector2D Vector2D::operator/(const Vector2D& other){
    return Vec_Div(&v, &other.v);
}

void Vector2D::operator=(const Vector2D& other){
    v.x = other.v.x;
    v.y = other.v.y;
}

bool Vector2D::operator==(const Vector2D& other){
    return (v.x==other.v.x) && (v.y==other.v.y);
}

float Vector2D::operator^(const Vector2D& other){
    return Vec_Cross(&v, &other.v);
}

Vector2D Vector2D::operator+=(const Vector2D& other){
    *this  = *this+other;
    return v;
}

Vector2D Vector2D::operator-=(const Vector2D& other){
    *this = *this-other;
    return *this;
}

float Vector2D::operator*=(const Vector2D& other){
    return *this*other;
}

Vector2D Vector2D::operator/=(const Vector2D& other){
    *this = *this/other;
    return *this;
}

float Vector2D::operator^=(const Vector2D& other){
    return *this^other;
}

float Vector2D::GetLen() const{
    return Vec_GetLen(&v);
}

void Vector2D::Rotate(float angle){
    Vec_RotateSelf(&v, angle);
}

Vector Vector2D::GetVector() {
    return v;
}

float Vector2D::Dot(const Vector2D& other) const{
    return Vec_Dot(&v, &other.v);
}

float Vector2D::Cross(const Vector2D& other) const{
    return Vec_Cross(&v, &other.v);
}

void Vector2D::Normalize(){
    Vec_NormalizeSelf(&v);
}

Vector2D Normalize(const Vector2D& v){
    Vector tmp = {v.GetX(), v.GetY()};
    return Vec_Normalize(&tmp);
}

Vector2D Rotate(const Vector2D& v, float angle){
    Vector tmp = {v.GetX(), v.GetY()};
    return Vec_Rotate(&tmp, angle);
}
