/**
 * @file main.c
 * @VisualGMQ
 * @brief the main file
 * @version 0.1
 * @date 2019-09-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <stdio.h>
#include "SDL.h"
#include "error.h"
#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define DELAY_TIME 60

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("I wanna riding the bike!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(!window){
        perror("window not created");
        return WINDOW_ERROR;
    }
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    if(!render){
        perror("render not created");
        return RENDER_ERROR;
    }

    SDL_bool isquit = SDL_FALSE;
    SDL_Event event;
    while(!isquit){
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = SDL_TRUE;
        }
        SDL_RenderPresent(render);
        SDL_Delay(DELAY_TIME);
    }

    SDL_Quit();
}