#ifndef __COLLISION_H__
#define __COLLISION_H__
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include "geomentry.h"
#include "mmath.h"

bool RectPoint(SDL_Rect rect, SDL_Point point);
bool RectRect(SDL_Rect rect1, SDL_Rect rect2);
bool RectLine(SDL_Rect rect, SDL_Line line);
bool CircleCircle(SDL_Circle c1, SDL_Circle c2);
//TODO 实现这些碰撞函数

bool CircleRect(SDL_Rect rect, SDL_Circle circle);
bool SAT(SDL_Point poly1[], SDL_Point poly2[]);

#endif