#include "UI.h"

void mouseDrag(SDL_Event* event, void* item){
    UI_MoveItem(item, event->motion.x, event->motion.y);
}

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test UI_Image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    UI_Init(render);
    bool isquit = false;
    SDL_Event event;
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    //break point
    UI_Image* image = UI_CreateImage("resources/image.bmp", NULL);
    UI_SetMouseMotionEvent(image, mouseDrag);
    UI_MoveItem(image, 200, 200);

    SDL_Size size = UI_GetSize(image);
    while(!isquit){
        SDL_RenderClear(render);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
            _eventDeliver(&event, image);
        }

        if(size.w >= 200){
            size.w = 10;
            size.h = 10;
        }else{
            size.w+=2;
            size.h+=2;
        }
        UI_SetSize(image, size.w, size.h);
        UI_DrawImage(image);
        SDL_RenderPresent(render);
        SDL_Delay(60);
    }
    UI_DestroyImage(image);
    UI_Quit();
    SDL_Quit();
    return 0;
}