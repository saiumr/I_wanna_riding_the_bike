#include "engin/geomentry.hpp"

void RotateRectangle(SDL_Point ret_array[], SDL_Point* center, SDL_Rect* rect, real degree){
    ret_array[0].x = rect->x;
    ret_array[0].y = rect->y;
    ret_array[1].x = rect->x+rect->w;
    ret_array[1].y = rect->y;
    ret_array[2].x = rect->x+rect->w;
    ret_array[2].y = rect->y+rect->h;
    ret_array[3].x = rect->x;
    ret_array[3].y = rect->y+rect->h;
    SDL_Point c;
    if(center==nullptr){
        c.x = (ret_array[0].x+ret_array[2].x)/2;
        c.y = (ret_array[0].y+ret_array[2].y)/2;
    }else
        c = *center;
    RotatePointGroup(&c, ret_array, 4, degree);
}

void RotRect2Points(SDL_Point ret_array[], SDL_Point* center,  SDL_RotRect* rrect){
    RotateRectangle(ret_array, center, &rrect->rect, rrect->degree);
}

SDL_Point GetRectangleCenter(SDL_Rect* rect){
    SDL_Point center = {(rect->x+rect->w)/2, (rect->y+rect->h)/2};
    return center;
}

float GetRotRectAngle(SDL_Point vertices[]){
    int x = vertices[0].x-vertices[1].x,
        y = vertices[0].y-vertices[1].y;
    if(x == 0 || y == 0)
        return 0;
    float degree = Radian2Degree(atan(y/(double)x));
    if(degree < 0)
        degree+=360;
    return degree;
}