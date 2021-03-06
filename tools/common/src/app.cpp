//
// Created by 桂明谦 on 2019/12/31.
//

#include "app.hpp"

App::App(const string& title, int width, int height, Uint32 flag):isquit(false),size({width, height}){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    TTF_Init();
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flag);
    if(window==nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "window create failed");
        Quit();
    }
    render = SDL_CreateRenderer(window, -1, 0);
    if(render==nullptr){
        SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "render create failed");
        Quit();
    }
}

App::MouseInfo::MouseInfo():pos({0, 0}){
    button[SDL_BUTTON_LEFT] = false;
    button[SDL_BUTTON_RIGHT] = false;
    button[SDL_BUTTON_MIDDLE] = false;
}

SDL_Point App::GetOriginalSize(){
    return size;
}

void App::EventHandle(SDL_Event& event){
    if(event.type==SDL_QUIT)
        OnExit();
    if(event.type==SDL_KEYDOWN)
        if(event.key.keysym.sym == SDLK_ESCAPE)
            OnExit();
    if(event.type==SDL_WINDOWEVENT_RESIZED){
        SDL_Point newsize = {event.window.data1, event.window.data2};
        SDL_Point size = GetOriginalSize();
        //FIXME 这种方式，以及绘制在Texture上再blit到屏幕上的方式都会导致一定程度的失真。后期最好还是改一下
        SDL_RenderSetScale(render, newsize.x/static_cast<double>(size.x),
                                           newsize.y/static_cast<double>(size.y));
    }
    if(event.type==SDL_MOUSEBUTTONDOWN){
        mouseinfo.button[event.button.button] = true;
    }
    if(event.type==SDL_MOUSEBUTTONUP){
        mouseinfo.button[event.button.button] = false;
    }
    if(event.type==SDL_MOUSEMOTION){
        mouseinfo.pos.x = event.motion.x;
        mouseinfo.pos.y = event.motion.y;
    }
}

void App::Quit(){
    isquit = true;
}

void App::OnExit() {
    Quit();
}

App::MouseInfo& App::GetMouseInfo(){
    return mouseinfo;
}

App::~App(){
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

void App::Run(){
    SDL_Event event;
    while(!isquit){
        SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
        SDL_RenderClear(render);
        while(SDL_PollEvent(&event)){
            EventHandle(event);
        }
        Update();
        SDL_RenderPresent(render);
        SDL_Delay(delay_time);
    }
}
