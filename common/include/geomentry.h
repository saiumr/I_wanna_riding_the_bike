#ifndef __GEOMENTRY_H__
#define __GEOMENTRY_H__
#include "SDL.h"
#include "header.h"
#include "mmath.h"

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

SDL_Point GetRectangleCenter(SDL_Rect* rect);

float GetRotRectAngle(SDL_Point vertices[]);
void RotateRectangle(SDL_Point ret_array[], SDL_Point* center, SDL_Rect* rect, real degree);
void RotRect2Points(SDL_Point ret_array[], SDL_Point* center, SDL_RotRect* rrect);

#endif