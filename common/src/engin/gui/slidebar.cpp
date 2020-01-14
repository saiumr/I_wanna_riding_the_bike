//
// Created by 桂明谦 on 2020/1/14.
//

#include "engin/gui/slidebar.hpp"

using namespace GUI;

const int SlideBar::DefaultLen = 200;
const SlideBar::Type SlideBar::DefaultType = SlideBar::Type::HORIZONTAL;
const SDL_Size SlideBar::ButtonSize = {15, 30};

SlideBar::SlideBar(int minvalue, int maxvalue, int length, Type t):button_pressed(false),min_value(minvalue),max_value(maxvalue),len(length),value(min_value),type(t){}

float SlideBar::GetValue() const{
    return value;
}

void SlideBar::SetValue(float v){
    if(v>=min_value && v<=max_value)
        value = v;
}

SlideBar::Type SlideBar::GetType() const{
    return type;
}

void SlideBar::SetType(Type t){
    type = t;
}

void SlideBar::EventHandle(SDL_Event& event){
    float prop = static_cast<float>(value-min_value)/(max_value-min_value);
    SDL_Rect button_rect;
    switch(type) {
        case Type::HORIZONTAL:
            button_rect = {rect.x + static_cast<int>(prop * len) - ButtonSize.w/2, rect.y-ButtonSize.h/2, ButtonSize.w, ButtonSize.h};
            break;
        case Type::VERTICAL:
            button_rect = {rect.x - ButtonSize.h / 2, rect.y + static_cast<int>(prop * len) - ButtonSize.w/2, ButtonSize.h, ButtonSize.w};
            break;
    }
    if(event.type==SDL_MOUSEBUTTONDOWN){
        SDL_Point mouse_pos = {event.button.x, event.button.y};
        if(SDL_PointInRect(&mouse_pos, &button_rect))
            button_pressed = true;
    }
    if(event.type==SDL_MOUSEBUTTONUP)
        button_pressed = false;
    if(event.type==SDL_MOUSEMOTION && button_pressed){
        float value_delta = max_value-min_value;
        switch(type){
            case Type::HORIZONTAL:
                value = min_value + std::min<double>(std::max<double>(0.0, (event.button.x-rect.x)/ static_cast<double>(len)), 1.0)*value_delta;
                break;
            case Type::VERTICAL:
                value = min_value + std::min<double>(std::max<double>(0.0, (event.button.y-rect.y)/ static_cast<double>(len)), 1.0)*value_delta;
                break;
        }
    }
}

bool SlideBar::QueryState(unsigned int s) const {
    return false;
}

void SlideBar::update(){}

float SlideBar::GetMinValue() const{
    return min_value;
}

float SlideBar::GetMaxValue() const{
    return max_value;
}

void SlideBar::SetMinValue(float v){
    min_value = v;
}

void SlideBar::SetMaxValue(float v){
    max_value = v;
}

void SlideBar::Resize(int len){
    this->len = len;
}

void SlideBar::draw(){
    drawBar();
    drawButton();
    drawText();
}

void SlideBar::drawButton(){
    float prop = (value-min_value)/(max_value-min_value);
    SDL_Renderer* render = GUIResourceManager::GetRender();
    SDL_Rect button_rect;
    switch(type) {
        case Type::HORIZONTAL:
            button_rect = {rect.x + static_cast<int>(prop * len) - ButtonSize.w/2, rect.y-ButtonSize.h/2, ButtonSize.w, ButtonSize.h};
            break;
        case Type::VERTICAL:
            button_rect = {rect.x - ButtonSize.h / 2, rect.y + static_cast<int>(prop * len) - ButtonSize.w/2, ButtonSize.h, ButtonSize.w};
            break;
    }
    SDL_SetRenderDrawColor(render, 200, 200, 200, 255);
    SDL_RenderFillRect(render, &button_rect);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderDrawRect(render, &button_rect);
}

void SlideBar::drawText(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    FC_Font* font = FC_CreateFont();
    FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), 10, FC_MakeColor(0, 0, 0, 255), TTF_STYLE_NORMAL);
    stringstream ss;
    ss<<min_value;
    const char* str_minvalue = ss.str().c_str();
    ss.str("");
    ss<<max_value;
    const char* str_maxvalue = ss.str().c_str();
    ss.str("");
    ss<<value;
    const char* str_value = ss.str().c_str();
    ss.str("");
    switch(type) {
        case Type::HORIZONTAL:
            //draw minvalue
            FC_Draw(font, render, rect.x-FC_GetWidth(font, str_minvalue)/2, rect.y + 20, str_minvalue);
            //draw value
            FC_Draw(font, render, rect.x+len/2-FC_GetWidth(font, str_value)/2, rect.y+20, str_value);
            //draw maxvalue
            FC_Draw(font, render, rect.x+len-FC_GetWidth(font, str_minvalue)/2, rect.y + 20, str_maxvalue);
            break;
        case Type::VERTICAL:
            //draw minvalue
            FC_Draw(font, render, rect.x+20, rect.y-FC_GetHeight(font, str_minvalue)/2, str_minvalue);
            //draw value
            FC_Draw(font, render, rect.x+20, rect.y+len/2-FC_GetHeight(font,str_value)/2, str_value);
            //draw maxvalue
            FC_Draw(font, render, rect.x+20, rect.y+len-FC_GetHeight(font, str_maxvalue)/2, str_maxvalue);
            break;
    }
    FC_FreeFont(font);
}

void SlideBar::drawBar(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
    switch(type){
        case Type::HORIZONTAL:
            SDL_RenderDrawLine(render, rect.x, rect.y, rect.x+len, rect.y);
            SDL_RenderDrawLine(render, rect.x, rect.y-10, rect.x, rect.y+10);
            SDL_RenderDrawLine(render, rect.x+len, rect.y-10, rect.x+len, rect.y+10);
            break;
        case Type::VERTICAL:
            SDL_RenderDrawLine(render, rect.x, rect.y, rect.x, rect.y+len);
            SDL_RenderDrawLine(render, rect.x-10, rect.y, rect.x+10, rect.y);
            SDL_RenderDrawLine(render, rect.x-10, rect.y+len, rect.x+10, rect.y+len);
            break;
    }
}
