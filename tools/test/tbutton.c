#include "UI.h"

void clickFunction(SDL_Event* event, void* item){
    log_debug("clicked this button!");
    UI_Button* button = (UI_Button*)item;
    strcpy(button->text, "clicked");
}

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("test UI_Button", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);
    SDL_Renderer* render = SDL_CreateRenderer(window, -1, 0);
    UI_Init(render);
    bool isquit = false;
    SDL_Event event;
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);

    UI_Button* button = UI_CreateButton("button1", clickFunction, NULL);
    UI_MoveItem(button, 200, 200);
    Uint8* fontsize = &button->displayinfo.fontsize;
    while(!isquit){
        SDL_RenderClear(render);

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT)
                isquit = true;
            _eventDeliver(&event, button);
        }

        (*fontsize)+=1;
        if(*fontsize >= 100)
            *fontsize = 0;

        _fixButtonSize(button);

        UI_DrawButton(button);
        SDL_RenderPresent(render);
        SDL_Delay(60);
    }
    UI_DestroyButton(button);
    UI_Quit();
    SDL_Quit();
    return 0;
}