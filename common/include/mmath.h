#ifndef __MMATH_H__
#define __MMATH_H__

#include "SDL.h"
#include "header.h"
#include "math.h"

typedef SDL_Pointf SDL_Vector;

SDL_Vector  Vec_CreateVec(const float x1, const float y1, const float x2, const float y2);
SDL_Vector  Vec_CreateVecByPoints(const SDL_Point* p1, const SDL_Point* p2);
SDL_Vector  Vec_Add(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Sub(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Mul(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Div(const SDL_Vector* v1, const SDL_Vector* v2);

float       Vec_Dot(const SDL_Vector* v1, const SDL_Vector* v2);
float       Vec_Cross(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Normalize(const SDL_Vector* v);
void        Vec_NormalizeSelf(SDL_Vector* v); 
float       Vec_GetLen(const SDL_Vector* v);
float       Vec_GetAngle(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Rotate(SDL_Vector* v, float degree);
void        Vec_RotateSelf(SDL_Vector* v, float degree);

void        RotatePointSelf(SDL_Point* center, SDL_Point* point, float degree);
void        RotatePointGroup(SDL_Point* center, SDL_Point* points, int num, float degree);
SDL_Point   RotatePoint(SDL_Point* center, SDL_Point point, float degree);

float Degree2Radian(float degree);
float Radian2Degree(float radian);

float GetDistance(float x1, float y1, float x2, float y2);

double min(double a, double b);
double max(double a, double b);
float minf(float a, float b);
float maxf(float a, float b);

#endif