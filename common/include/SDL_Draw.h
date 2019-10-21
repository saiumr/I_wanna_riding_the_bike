#ifndef __SDL_DRAW_H__
#define __SDL_DRAW_H__

#include <stdbool.h>
#include <math.h>
#include "SDL.h"
#include "mmath.h"

void SDL_RenderDrawCircle(SDL_Renderer* render, int x, int y, int r);
void SDL_RenderDrawCloseLines(SDL_Renderer* render, SDL_Point points[], const int num);
void SDL_RenderDrawRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree);
void SDL_RenderFillRectEx(SDL_Renderer* render, SDL_Rect* rect, SDL_Point* center, double degree);
void SDL_RenderFillPolygon(SDL_Renderer* render, SDL_Point points[]);

#endif