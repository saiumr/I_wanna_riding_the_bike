//
// Created by 桂明谦 on 2019/11/29.
//

#ifndef __SHAPE_HPP__
#define __SHAPE_HPP__
#include "SDL.h"

struct SDL_Size{
    int w;
    int h;
};

struct SDL_Pointf{
    float x;
    float y;
    SDL_Pointf(){
        x = 0;
        y = 0;
    }
    SDL_Pointf(const SDL_Point p){
        x = p.x;
        y = p.y;
    }
    SDL_Pointf(const float x, const float y){
        this->x = x;
        this->y = y;
    }
    SDL_Pointf(const int x, const int y){
        this->x = x;
        this->y = y;
    }
    bool operator==(const SDL_Pointf& p) const{
        return p.x==x&&p.y==y;
    }
};

struct SDL_Circle{
    SDL_Point    center;
    unsigned int r;
};

struct SDL_Line{
    SDL_Point p1;
    SDL_Point p2;
};

struct SDL_RotRect{
    SDL_Rect rect;
    float     degree;
};

#endif
