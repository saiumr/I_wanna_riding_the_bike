//
// Created by 桂明谦 on 2020/1/4.
//

#include "engin/collisionapproch.hpp"
#include "guitestframework.hpp"

class Test:public GUITestframework{
public:
    Test():GUITestframework("Rect collide Rect", 800, 600, SDL_WINDOW_SHOWN),rect1({100, 100, 50, 50}), rect2({400, 400, 50, 50}){
    }

    void Update() override{
        HandleMovement();
        if(RectRect(rect1, rect2)){
            Vector2D speed(rect1.x-oldpos.x, rect1.y-oldpos.y);
            RectCollisionInfo info = GetRectRectInfo(rect1, speed, rect2);
            HandleRectColliWithInfo(rect1, rect2, info);
        }
        oldpos.x = rect1.x;
        oldpos.y = rect1.y;
        DrawRects();
    }

    void DrawSnapshot(){
        SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, 800, 600, 32, SDL_PIXELFORMAT_RGBA8888);
        SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 100, 100, 100));
        SDL_FillRect(surface, &rect2, SDL_MapRGB(surface->format, 255, 255, 0));
        SDL_FillRect(surface, &rect1, SDL_MapRGB(surface->format, 0, 255, 0));
        IMG_SavePNG(surface, "debug.png");
    }

    void HandleMovement(){
        if(KeyPressing(SDLK_w))

            rect1.y -= Speed;
        if(KeyPressing(SDLK_s))
            rect1.y += Speed;
        if(KeyPressing(SDLK_a))
            rect1.x -= Speed;
        if(KeyPressing(SDLK_d))
            rect1.x += Speed;
    }

    void DrawRects(){
        SDL_SetRenderDrawColor(render, 0, 100, 0, 255);
        SDL_RenderDrawRect(render, &rect1);
        SDL_SetRenderDrawColor(render, 150, 0, 150, 255);
        SDL_RenderDrawRect(render, &rect2);
    }
private:
    const int Speed = 1;
    SDL_Rect rect1;
    SDL_Rect rect2;
    SDL_Point oldpos;
};

RUN_APP(Test)

