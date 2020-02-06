#ifndef __MMATH_H__
#define __MMATH_H__

#include "SDL.h"
#include <stdbool.h>
#include <math.h>
#define EPS 0.00001
#define Degree2Radian(x) (x*M_PI/180.0)
#define Radian2Degree(x) (x*180.0f/M_PI)

typedef SDL_Point Point;
typedef SDL_Rect Rect;

typedef float real;

typedef struct{
    int w;
    int h;
}SDL_Size;

typedef struct{
    SDL_Point       center;
    unsigned int    r;
}SDL_Circle;

typedef struct{
    SDL_Point p1;
    SDL_Point p2;
}SDL_Line;

typedef struct{
    SDL_Rect    rect;
    float       degree;
}SDL_RotRect;

typedef struct{
    float x;
    float y;
}Pointf;

typedef Pointf SDL_Pointf;

typedef struct{
    float x;
    float y;
    float w;
    float h;
}Rectf;

SDL_Rect Rectf2Rect(Rectf* rectf);

typedef Rectf SDL_Rectf;

typedef Pointf Vector;
typedef Vector SDL_Vector;

Vector  Vec_CreateVec(const float x1, const float y1, const float x2, const float y2);
Vector  Vec_CreateVecByPoints(const Point* p1, const Point* p2);
Vector  Vec_Add(const Vector* v1, const Vector* v2);
Vector  Vec_Sub(const Vector* v1, const Vector* v2);
Vector  Vec_Mul(const Vector* v1, const Vector* v2);
Vector  Vec_Div(const Vector* v1, const Vector* v2);

float       Vec_Dot(const Vector* v1, const Vector* v2);
float       Vec_Cross(const Vector* v1, const Vector* v2);
Vector  Vec_Normalize(const Vector* v);
void        Vec_NormalizeSelf(Vector* v);
float       Vec_GetLen(const Vector* v);
float       Vec_GetAngle(const Vector* v1, const Vector* v2);
Vector  Vec_Rotate(Vector* v, float degree);
void        Vec_RotateSelf(Vector* v, float degree);

void        RotatePointSelf(Point* center, Point* point, float degree);
void        RotatePointGroup(Point* center, Point* points, int num, float degree);
Point   RotatePoint(Point* center, Point point, float degree);

float GetDistance(float x1, float y1, float x2, float y2);

double min(double a, double b);
double max(double a, double b);
float minf(float a, float b);
float maxf(float a, float b);

#endif