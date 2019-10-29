#ifndef __GEOMENTRY_H__
#define __GEOMENTRY_H__

typedef struct{
    SDL_Point       center;
    unsigned int    r;
}SDL_Circle;

typedef struct{
    SDL_Point p1;
    SDL_Point p2;
}SDL_Line;

#endif