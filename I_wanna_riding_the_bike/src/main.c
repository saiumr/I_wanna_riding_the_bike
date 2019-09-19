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
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"

#include "log.h"
#include "error.h"
#define WIN_WIDTH   800
#define WIN_HEIGHT  800
#define FPS         60
#define DELAY_TIME  1000.0f/FPS
#define PI          3.1415926

int main(int argc, char** argv){
    float angle = 0;
    float passedtime = 0;
    int radius = 50;
    setLogLevel(LOG_ERROR);
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("I wanna riding the bike!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(!window){
        log_error("window create failed");
        return WINDOW_ERROR;
    }
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    if(!render){
        log_error("render created failed");
        return RENDER_ERROR;
    }

    SDL_bool isquit = SDL_FALSE;
    SDL_Event event;

    SDL_Surface* surface = IMG_Load("resources/testImage.png");
    if(!surface){
        log_error("image load failed");
        return IMAGE_ERROR;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_Rect dstrect = {0, 0, surface->w*10, surface->h*10};
    SDL_FreeSurface(surface);

    while(!isquit){
        int i,j;
        passedtime = SDL_GetTicks();
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = SDL_TRUE;
        }
        float radian = angle*PI/180;
        SDL_Rect rect = dstrect;
        for(i=0;i<WIN_WIDTH/dstrect.w;i++)
            for(j=0;j<WIN_HEIGHT/dstrect.h;j++){
                rect.x = dstrect.w*i+radius*cos(radian)+50;
                rect.y = dstrect.h*j+radius*sin(radian)+50;
                SDL_RenderCopy(render, texture, NULL, &rect);
            }
        angle+=2;
        if(angle >= 360)
            angle-=360;
        SDL_RenderPresent(render);
        int resttime = SDL_GetTicks() - passedtime;
        if(resttime <= DELAY_TIME)
            SDL_Delay(DELAY_TIME-resttime);
    }

    SDL_DestroyRenderer(render);
    SDL_Quit();
}