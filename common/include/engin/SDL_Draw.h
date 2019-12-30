#ifndef __SDL_DRAW_H__
#define __SDL_DRAW_H__

#include "geomentry.h"

void SDL_RenderDrawCircle(SDL_Renderer* render, int x, int y, int r);
void SDL_RenderDrawCloseLines(SDL_Renderer* render, SDL_Point points[], const int num);
void SDL_RenderDrawRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree);
//TODO not finish
void SDL_RenderFillRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree);
void SDL_RenderFillPolygon(SDL_Renderer* render, SDL_Point points[]);

void SDL_RenderDrawWidthLine(SDL_Renderer* render, SDL_Point* p1, SDL_Point* p2, int width);
void SDL_RenderDrawWidthRectEx(SDL_Renderer* render, SDL_Rect* rect, real degree, int width);
void SDL_RenderDrawCloseWidthLines(SDL_Renderer* render, SDL_Point* points, int width, int num);
#endif