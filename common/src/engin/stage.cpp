#include "engin/stage.hpp"

SDL_Event Stage::event;

void Stage::Run(){
    Director* director = Director::GetDirector();
    while(!director->IsQuit()){
        Uint32 t = SDL_GetTicks();
        const int delaytime = 1.0/director->GetFPS()*1000;
        eventHandle();
        if(!director->isLostFocus){
            SDL_Renderer* render = director->GetRender();
            SDL_SetRenderDrawColor(render, director->clear_color.r, director->clear_color.g, director->clear_color.b, director->clear_color.a);
            SDL_RenderClear(render);
            director->GetCurrentScene()->Update();
            SDL_RenderPresent(render);
        }
        t = SDL_GetTicks() - t;
        controllerUpdate();
        SDL_Delay((t<delaytime)?delaytime-t:delaytime);
    }
}

void Stage::eventHandle(){
    Director* director = Director::GetDirector();
    Controller* controller = Controller::GetController();
    while(SDL_PollEvent(&event)){
        if(controller)
            controller->EventHandle(event);

        if(event.type == SDL_QUIT)
            director->ExitGame(NO_ERROR);
        if(event.type == SDL_WINDOWEVENT){
            Uint8 type = event.window.event;
            //NOTE 这里我们只侦测键盘的焦点有没有丢失，不管鼠标的
            if(type == SDL_WINDOWEVENT_FOCUS_LOST /*|| type == SDL_WINDOWEVENT_LEAVE*/){
                director->isLostFocus = true;
            }
            if(type == SDL_WINDOWEVENT_FOCUS_GAINED /*|| type == SDL_WINDOWEVENT_ENTER*/){
                director->isLostFocus = false;
            }
            if(type == SDL_WINDOWEVENT_RESIZED){
                director->window_width = event.window.data1;
                director->window_height = event.window.data2;
                //FIXME 这种方式，以及绘制在Texture上再blit到屏幕上的方式都会导致一定程度的失真。后期最好还是改一下
                SDL_RenderSetScale(director->GetRender(), director->GetWindowWidth()/static_cast<double>(director->GetCanvaWidth()),
                                                          director->GetWindowHeight()/static_cast<double>(director->GetCanvaHeight()));
            }
        }
        if(event.type == SDL_KEYDOWN){
            //F10切换全屏
            if(event.key.keysym.sym == SDLK_F10)
                director->ToggleFullScreen();

        }
        if(!director->isLostFocus)
            director->GetCurrentScene()->EventHandle(event);
    }
}

void Stage::controllerUpdate(){
    Controller* controller = Controller::GetController();
    if(controller)
        controller->Update();
}
