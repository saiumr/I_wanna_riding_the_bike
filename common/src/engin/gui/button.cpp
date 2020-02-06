//
// Created by 桂明谦 on 2020/1/6.
//

#include "engin/gui/button.hpp"

using namespace GUI;

Button::Button():IButton(),backgroundColor({156, 156, 156, 255}),foregroundColor({0, 0, 0, 255}){
    Resize(50, 20);
}

Button::Button(const string text, int x, int y, int w, int h):IButton(x, y, w, h),foregroundColor({0, 0, 0, 255}),backgroundColor({156, 156, 156, 255}){
    this->text = text;
}

void Button::SetBackgroundColor(int r, int g, int b, int a){
    backgroundColor.r = r;
    backgroundColor.g = g;
    backgroundColor.b = b;
    backgroundColor.a = a;
}

SDL_Color Button::GetBackgroundColor() const{
    return backgroundColor;
}

void Button::draw(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    FC_Font* font = FC_CreateFont();
    const int font_size = 20;
    FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), font_size, foregroundColor, TTF_STYLE_NORMAL);
    if(QueryState(NORMAL)||QueryState(MOUSE_MOVING)){
        SDL_SetRenderDrawColor(render, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    }
    if(QueryState(PRESSING)||QueryState(PRESSED)){
        float alpha = dark_cover.a/255.0;
        SDL_SetRenderDrawColor(render, backgroundColor.r*(1-alpha)+dark_cover.r*alpha,
                                       backgroundColor.g*(1-alpha)+dark_cover.g*alpha,
                                       backgroundColor.b*(1-alpha)+dark_cover.b*alpha,
                                       255);
    }
    SDL_Rect rrect = Rectf2Rect(&rect);
    SDL_RenderFillRect(render, &rrect);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    SDL_RenderDrawRect(render, &rrect);
    if(font) {
        const int text_width = FC_GetWidth(font, text.c_str()),
                    text_height = FC_GetHeight(font, text.c_str());
        FC_Draw(font, render, rect.x + rect.w/2 - text_width/2, rect.y+rect.h/2 - text_height/2, text.c_str());
    }else
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "can't load ttf");
    FC_FreeFont(font);
}
