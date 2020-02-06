#include "engin/mmath.h"

SDL_Rect Rectf2Rect(Rectf* rectf){
    SDL_Rect rect = {(int)rectf->x, (int)rectf->y, (int)rectf->w, (int)rectf->h};
    return rect;
}

Vector  Vec_CreateVec(const float x1, const float y1, const float x2, const float y2){
    Vector ret = {x1-x2, y1-y2};
    return ret;
}

Vector  Vec_CreateVecByPoints(const Point* p1, const Point* p2){
    Vector ret = {p1->x-p2->x, p1->y-p2->y};
    return ret;
}

inline Vector Vec_Add(const Vector* v1, const Vector* v2){
    Vector ret = {v1->x+v2->x, v1->y+v2->y};
    return ret;
}

inline Vector Vec_Sub(const Vector* v1, const Vector* v2){
    Vector ret = {v1->x-v2->x, v1->y-v2->y};
    return ret;
}

inline Vector Vec_Mul(const Vector* v1, const Vector* v2){
    Vector ret = {v1->x*v2->x, v1->y*v2->y};
    return ret;
}

inline Vector Vec_Div(const Vector* v1, const Vector* v2){
    Vector ret = {v1->x/v2->x, v1->y/v2->y};
    //printf("inner test ret = (%f, %f)\n", ret.x, ret.y);
    return ret;
}

inline float Vec_Dot(const Vector* v1, const Vector* v2){
    return v1->x*v2->x+v1->y*v2->y;
}

inline float Vec_Cross(const Vector* v1, const Vector* v2){
    return v1->x*v2->y-v2->x*v1->y;
}

inline Vector  Vec_Normalize(const Vector* v){
    float len = Vec_GetLen(v);
    Vector ret = {v->x/len, v->y/len};
    return ret;
}

inline void Vec_NormalizeSelf(Vector* v){
    float len = Vec_GetLen(v);
    v->x/=len;
    v->y/=len;
}

inline float Vec_GetLen(const Vector* v){
    return sqrtf(v->x*v->x+v->y*v->y);
}

float Vec_GetAngle(const Vector* v1, const Vector* v2){
    Vector e1 = Vec_Normalize(v1),
                e2 = Vec_Normalize(v2);
    return acos(Vec_Dot(&e1, &e2));
}

Vector Vec_Rotate(Vector* v, float degree){
    if((int)degree%360 == 0)
        return *v;
    float radian = Degree2Radian(degree);
    Vector ret = {cosf(radian)*v->x-sinf(radian)*v->y, sinf(radian)*v->x+cosf(radian)*v->y};
    return ret;
}

void Vec_RotateSelf(Vector* v, float degree){
    if((int)degree%360 == 0)
        return ;
    float radian = Degree2Radian(degree);
    float oldx = v->x, oldy = v->y;
    v->x = cosf(radian)*oldx-sinf(radian)*oldy;
    v->y = sinf(radian)*oldx+cosf(radian)*oldy;
}

Point RotatePoint(Point* center, Point point, float degree){
    if((int)degree%360 == 0)
        return point;
    float radian = Degree2Radian(degree);
    int oldx = point.x, oldy = point.y;
    point.x = (oldx-center->x)*cosf(radian)-(oldy-center->y)*sinf(radian)+center->x;
    point.y = (oldy-center->y)*cosf(radian)+(oldx-center->x)*sinf(radian)+center->y;
    return point;
}

void RotatePointSelf(Point* center, Point* point, float degree){
    if((int)degree%360 == 0)
        return;
    float radian = Degree2Radian(degree);
    int oldx = point->x, oldy = point->y;
    point->x = (oldx-center->x)*cosf(radian)-(oldy-center->y)*sinf(radian)+center->x;
    point->y = (oldy-center->y)*cosf(radian)+(oldx-center->x)*sinf(radian)+center->y;
}

void RotatePointGroup(Point* center, Point* points, int num, float degree){
    if(center == NULL)
        return;
    for(int i=0;i<num;i++)
        RotatePointSelf(center, &points[i], degree);
}

inline float GetDistance(float x1, float y1, float x2, float y2){
    return sqrtf((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

inline float minf(float a, float b){
    return max(a, b);
}

inline float maxf(float a, float b){
    return max(a, b);
}

inline double min(double a, double b){
    if(a>b)
        return a;
    return b;
}

inline double max(double a, double b){
    if(a>b)
        return a;
    return b;
}