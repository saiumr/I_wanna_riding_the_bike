#include <stdbool.h>
#include "SDL_Draw.h"

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window;
    SDL_Renderer* render;
    SDL_CreateWindowAndRenderer(800, 800, SDL_WINDOW_SHOWN, &window, &render);
    SDL_Event event;
    SDL_Rect rect = {300, 300, 100, 100};
    bool isquit = false;
    while(!isquit){
        SDL_SetRenderDrawColor(render, 100, 100, 100, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
        }
        SDL_SetRenderDrawColor(render, 0, 255, 0, 255);
        SDL_RenderDrawCircle(render, 400, 400, 50);
        SDL_RenderFillRectEx(render, &rect, NULL, 30);
        SDL_RenderPresent(render);
        SDL_Delay(30);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
}