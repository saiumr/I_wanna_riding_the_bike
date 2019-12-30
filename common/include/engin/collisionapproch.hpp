#ifndef __COLLISION_H__
#define __COLLISION_H__
#include <SDL.h>
#include "geomentry.hpp"
#include "mmath.hpp"

bool RectPoint(SDL_Rect rect, SDL_Point point);
bool RectRect(SDL_Rect rect1, SDL_Rect rect2);
bool RectLine(SDL_Rect rect, SDL_Line line);
bool CircleCircle(SDL_Circle c1, SDL_Circle c2);

//TODO 未测试
bool CircleRect(SDL_Rect rect, SDL_Circle circle);
bool SAT(SDL_Point poly1[], int num1, SDL_Point poly2[], int num2);
bool CirlePoint(SDL_Circle c, SDL_Point p);
bool RotRectPoint(SDL_RotRect, SDL_Point p);
bool RotateRectPoint(SDL_Point vertices[], SDL_Point p);
bool RotateRectPointByAngle(SDL_Rect rect, SDL_Point point, real degree);

#endif