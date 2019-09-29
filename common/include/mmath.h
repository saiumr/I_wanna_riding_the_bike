#ifndef __MMATH_H__
#define __MMATH_H__

#include "SDL.h"
#include "header.h"
#include "math.h"

typedef SDL_Pointf SDL_Vector;

SDL_Vector  Vec_Add(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Sub(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Mul(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Div(const SDL_Vector* v1, const SDL_Vector* v2);

float       Vec_Dot(const SDL_Vector* v1, const SDL_Vector* v2);
SDL_Vector  Vec_Normalize(const SDL_Vector* v);
void        Vec_NormalizeSelf(SDL_Vector* v); 
float       Vec_GetLen(const SDL_Vector* v);
/**
 * @brief 获得两个向量的夹角
 * 
 * @param v1 
 * @param v2 
 * @return float 返回弧度制夹角
 */
float       Vec_GetAngle(const SDL_Vector* v1, const SDL_Vector* v2);

float       Degree2Radian(float degree);
float       Radian2Degree(float radian);

#endif