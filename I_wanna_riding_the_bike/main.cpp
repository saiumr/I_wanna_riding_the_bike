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
#include "engin/engin.hpp"
#include "controllers/keyboardcontroller.hpp"
#include "scenes/welcomscene.hpp"

#define WIN_WIDTH   800
#define WIN_HEIGHT  800
#define FPS         60

int main(int argc, char** argv){
    InitEngin(new Director("I wanna riding the bike!", WIN_WIDTH, WIN_HEIGHT, FPS));
    Director::GetDirector()->ChanegScene(new WelcomeScene);
    KeyboardController controller;
    Controller::SetController(&controller);
    RunEngin();
    return QuitEngin();
    /*
    float angle = 0;
    float passedtime = 0;
    int radius = 50;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);

    FC_Font* font = FC_CreateFont();
    SDL_Window* window = SDL_CreateWindow("I wanna riding the bike!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(!window){
        spdlog::error("window create failed");
        return WINDOW_ERROR;
    }

    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    if(!render){
        spdlog::error("render created failed");
        return RENDER_ERROR;
    }

    FC_LoadFont(font, render, "resources/Fangsong.ttf", 20, FC_MakeColor(255, 255, 255, 255), TTF_STYLE_NORMAL);  
    bool isquit = false;
    SDL_Event event;
    SDL_Rect windowRect;
    windowRect.x = 0;
    windowRect.y = 0;
    windowRect.w = WIN_WIDTH;
    windowRect.h = WIN_HEIGHT;

    SDL_Surface* surface = IMG_Load("resources/testImage.png");
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0));
    SDL_Surface* surfaceBlack = IMG_Load("resources/black.png");
    if(!surface){
        spdlog::error("image load failed");
        return IMAGE_ERROR;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_Texture* textureBlack = SDL_CreateTextureFromSurface(render, surfaceBlack);
    SDL_SetTextureAlphaMod(textureBlack, 20);
    SDL_SetTextureBlendMode(textureBlack, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    SDL_Rect dstrect = {0, 0, surface->w*10, surface->h*10};
    SDL_FreeSurface(surface);


    while(!isquit){
        passedtime = SDL_GetTicks();
        SDL_RenderCopy(render, textureBlack, NULL, &windowRect);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
        }
        float radian = angle*M_PI/180;
        SDL_Rect rect = dstrect;

        for(int i=0;i<WIN_WIDTH/dstrect.w;i++)
            for(int j=0;j<WIN_HEIGHT/dstrect.h;j++){
                rect.x = dstrect.w*i+radius*cos(radian)+50;
                rect.y = dstrect.h*j+radius*sin(radian)+50;
                SDL_RenderCopy(render, texture, NULL, &rect);
            }
        angle+=2;
        if(angle >= 360)
            angle-=360;

        FC_Draw(font, render, 500, 750, "由 saiumr 和 VisualGMQ 制作");

        SDL_RenderPresent(render);
        int resttime = SDL_GetTicks() - passedtime;
        if(resttime <= DELAY_TIME)
            SDL_Delay(DELAY_TIME-resttime);
    }

    FC_FreeFont(font);
    SDL_DestroyRenderer(render);
    SDL_Quit();
    return 0;
     */
}