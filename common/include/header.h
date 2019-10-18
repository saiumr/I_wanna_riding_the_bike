#ifndef __HEADER_H__
#define __HEADER_H__
#include "SDL.h"
#include <assert.h>

#define Assert(exp) assert(exp)
//optional: #define Assert(exp) SDL_assert(exp)

typedef struct{
    int w;
    int h;
}SDL_Size;

typedef struct{
    float x;
    float y;
}SDL_Pointf;

#endif