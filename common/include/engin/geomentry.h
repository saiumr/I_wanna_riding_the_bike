#ifndef __GEOMENTRY_H__
#define __GEOMENTRY_H__
#include "SDL.h"
#include "mmath.h"

SDL_Point GetRectangleCenter(SDL_Rect* rect);

float GetRotRectAngle(SDL_Point vertices[]);
void RotateRectangle(SDL_Point ret_array[], SDL_Point* center, SDL_Rect* rect, real degree);
void RotRect2Points(SDL_Point ret_array[], SDL_Point* center, SDL_RotRect* rrect);

#endif