//
// Created by 桂明谦 on 2020/1/6.
//

#include "engin/gui/ibutton.hpp"

using namespace GUI;

SDL_Color IButton::dark_cover = {50, 50, 50, 200};

IButton::IButton():GUIComponent(),fgcolor({0, 0, 0, 255}),button_pressed(false),mouse_moved(false){}

IButton::IButton(int x, int y, int w, int h):GUIComponent(x, y, w, h),fgcolor({0, 0, 0, 255}),button_pressed(false),mouse_moved(false){}

void IButton::SetText(const string text){
    this->text = text;
}

string IButton::GetText(){
    return text;
}

SDL_Color IButton::GetForegroundColor(){
    return fgcolor;
}

void IButton::SetForegroundColor(int r, int g, int b, int a){
    fgcolor.r = r;
    fgcolor.g = g;
    fgcolor.b = b;
    fgcolor.a = a;
}

void IButton::EventHandle(SDL_Event& event){
    old_button_pressed = button_pressed;
    mouse_moved = false;
    if(event.type==SDL_MOUSEBUTTONDOWN) {
        SDL_Point point = {event.button.x, event.button.y};
        if (SDL_PointInRect(&point, &rect)) {
            button_pressed = true;
        }
    }
    if(event.type==SDL_MOUSEBUTTONUP) {
        if(old_button_pressed) {
            SDL_Point point = {event.button.x, event.button.y};
            if (SDL_PointInRect(&point, &rect)) {
                button_pressed = false;
            }
        }
    }
    if(event.type==SDL_MOUSEMOTION){
        SDL_Point point = {event.motion.x, event.motion.y};
        if(SDL_PointInRect(&point, &rect))
            mouse_moved = true;
    }
}

bool IButton::QueryState(unsigned int s){
    switch(s){
        case PRESSED:
            return !old_button_pressed&&button_pressed;
        case RELEASED:
            return old_button_pressed&&!button_pressed;
        case PRESSING:
            return old_button_pressed&&button_pressed;
        case MOUSE_MOVING:
            return mouse_moved;
        case NORMAL:
            return !old_button_pressed&&!button_pressed&&!mouse_moved;
    }
    return false;
}

void IButton::update(){
    old_button_pressed = button_pressed;
}
