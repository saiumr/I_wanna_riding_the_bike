//
// Created by 桂明谦 on 2020/1/6.
//

#include "engin/gui/ibutton.hpp"

IButton::IButton():GUIComponent(),button_pressed(false),state(NORMAL),clickCallBack(nullptr),buttonPressCallBack(nullptr),buttonReleaseCallBack(nullptr),mouseMoveCallBack(nullptr){}

IButton::IButton(int x, int y, int w, int h):GUIComponent(x, y, w, h),button_pressed(false),state(NORMAL),clickCallBack(nullptr),buttonReleaseCallBack(nullptr),buttonPressCallBack(nullptr),mouseMoveCallBack(nullptr){}

IButton::State IButton::GetState(){
    return state;
}

void IButton::SetText(const string text){
    this->text = text;
}

string IButton::GetText(){
    return text;
}

void IButton::EventHandle(SDL_Event& event){
        if(event.type==SDL_MOUSEBUTTONDOWN) {
            SDL_Point point = {event.button.x, event.button.y};
            if (SDL_PointInRect(&point, &rect)) {
                state = PRESSED;
                if (buttonPressCallBack)
                    buttonPressCallBack(event.button);
            }
        }
        if(event.type==SDL_MOUSEBUTTONUP) {
            if (state==PRESSED) {
                SDL_Point point = {event.button.x, event.button.y};
                if (SDL_PointInRect(&point, &rect))
                    if (clickCallBack)
                        clickCallBack(event.button);
                state = NORMAL;
                if (buttonReleaseCallBack)
                    buttonReleaseCallBack(event.button);
            }
        }
        if(event.type==SDL_MOUSEMOTION){
            SDL_Point point = {event.motion.x, event.motion.y};
            if(SDL_PointInRect(&point, &rect)){
                if(mouseMoveCallBack)
                    mouseMoveCallBack(event.motion);
            }
        }
}

void IButton::SetCallBack_ButtonPress(ButtonPress_CallBack ncallback) {
    buttonPressCallBack = ncallback;
}

void IButton::SetCallBack_ButtonRelease(ButtonRelease_CallBack ncallback){
    buttonReleaseCallBack = ncallback;
}

void IButton::SetCallBack_MouseMove(MouseMove_CallBack ncallback){
    mouseMoveCallBack = ncallback;
}

void IButton::SetCallBack_Click(Click_CallBack ncallback){
    clickCallBack = ncallback;
}
