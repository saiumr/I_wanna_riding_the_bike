#include "mmath.h"
#include <stdio.h>

SDL_Vector  Vec_CreateVec(const float x1, const float y1, const float x2, const float y2){
    SDL_Vector ret = {x1-x2, y1-y2};
    return ret;
}

inline SDL_Vector Vec_Add(const SDL_Vector* v1, const SDL_Vector* v2){
    SDL_Vector ret = {v1->x+v2->x, v1->y+v2->y};
    return ret;
}

inline SDL_Vector Vec_Sub(const SDL_Vector* v1, const SDL_Vector* v2){
    SDL_Vector ret = {v1->x-v2->x, v1->y-v2->y};
    return ret;
}

inline SDL_Vector Vec_Mul(const SDL_Vector* v1, const SDL_Vector* v2){
    SDL_Vector ret = {v1->x*v2->x, v1->y*v2->y};
    return ret;
}

inline SDL_Vector Vec_Div(const SDL_Vector* v1, const SDL_Vector* v2){
    SDL_Vector ret = {v1->x/v2->x, v1->y/v2->y};
    printf("inner test ret = (%f, %f)\n", ret.x, ret.y);
    return ret;
}

inline float Vec_Dot(const SDL_Vector* v1, const SDL_Vector* v2){
    return v1->x*v2->x+v1->y*v2->y;
}

inline SDL_Vector  Vec_Normalize(const SDL_Vector* v){
    float len = Vec_GetLen(v);
    SDL_Vector ret = {v->x/len, v->y/len};
    return ret;
}

inline void Vec_NormalizeSelf(SDL_Vector* v){
    float len = Vec_GetLen(v);
    v->x/=len;
    v->y/=len;
}

inline float Vec_GetLen(const SDL_Vector* v){
    return sqrtf(v->x*v->x+v->y*v->y);
}

float Vec_GetAngle(const SDL_Vector* v1, const SDL_Vector* v2){
    SDL_Vector e1 = Vec_Normalize(v1),
                e2 = Vec_Normalize(v2);
    return acos(Vec_Dot(&e1, &e2));
}

SDL_Vector Vec_Rotate(SDL_Vector* v, float degree){
    float radian = Degree2Radian(degree);
    SDL_Vector ret = {cosf(radian)*v->x-sinf(radian)*v->y, sinf(radian)*v->x+cosf(radian)*v->y};
    return ret;
}

void Vec_RotateSelf(SDL_Vector* v, float degree){
    float radian = Degree2Radian(degree);
    v->x = cosf(radian)*v->x-sinf(radian)*v->y;
    v->y = sinf(radian)*v->x+cosf(radian)*v->y;
}

inline float Degree2Radian(float degree){
    return degree*M_PI/180.0f;
}

inline float Radian2Degree(float radian){
    return radian*180.0f/M_PI;
}

inline float GetDistance(float x1, float y1, float x2, float y2){
    return sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}