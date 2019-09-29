#include "mmath.h"
#include <stdio.h>

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

inline float Degree2Radian(float degree){
    return degree*M_PI/180.0f;
}

inline float Radian2Degree(float radian){
    return radian*180.0f/M_PI;
}