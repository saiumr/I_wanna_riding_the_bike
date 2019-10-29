#include <stdbool.h>
#include "SDL.h"
#include "SDL_image.h"
#include "log.h"
#define DELAY_TIME 10

int main(int argc, char** argv){
    setLogLevel(LOG_ERROR);
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_Window* window = SDL_CreateWindow("MapEditor v0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(!window){
        log_error("window can't be create");
        return 1;
    }

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    if(!render){
        log_error("render can't be create");
        return 2;
    }

    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

    SDL_Event event;
    bool isquit = false;

    while(!isquit){
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
        }

        SDL_RenderPresent(render);
        SDL_Delay(DELAY_TIME);
    }

    SDL_Quit();
    return 0;
}
