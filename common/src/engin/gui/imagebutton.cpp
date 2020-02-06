//
// Created by 桂明谦 on 2020/1/10.
//

#include "engin/gui/imagebutton.hpp"
#include "engin/gui/guiexception.hpp"

using namespace GUI;

ImageButton::ImageButton(int x, int y, SDL_Texture* normal, SDL_Texture* press, float scalex, float scaley){
    Move(x, y);
    this->scalex = scalex;
    this->scaley = scaley;
    if(normal==nullptr || press==nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "image can't be nullptr");
        throw GUIException("image can't be nullptr");
    }else {
        SetNormalImage(normal);
        SetPressImage(press);
    }
}

void ImageButton::SetImage(SDL_Texture* normal, SDL_Texture* press) {
    SetPressImage(press);
    SetNormalImage(normal);
}

void ImageButton::draw(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    SDL_Rect rrect = Rectf2Rect(&rect);
    if(QueryState(PRESSED)||QueryState(PRESSING))
        SDL_RenderCopy(render, press_image, nullptr, &rrect);
    if(QueryState(NORMAL)||QueryState(MOUSE_MOVING))
        SDL_RenderCopy(render, normal_image, nullptr, &rrect);
    SDL_SetRenderDrawColor(render, fgcolor.r, fgcolor.g, fgcolor.b, fgcolor.a);
    FC_Font* font = FC_CreateFont();
    const int font_size = 20;
    FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), font_size, fgcolor, TTF_STYLE_NORMAL);
    if(font) {
        const int text_width = FC_GetWidth(font, text.c_str()),
                text_height = FC_GetHeight(font, text.c_str());
        FC_Draw(font, render, rect.x + rect.w/2 - text_width/2, rect.y+rect.h/2 - text_height/2, text.c_str());
    }else
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "can't load ttf");
    FC_FreeFont(font);
}

void ImageButton::SetNormalImage(SDL_Texture* image){
    if(image==nullptr)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "image can't be nullptr");
    else {
        normal_image = image;
        int w, h;
        SDL_QueryTexture(normal_image, nullptr, nullptr, &w, &h);
        Resize(static_cast<int>(w * scalex), static_cast<int>(h * scaley));
    }
}

void ImageButton::SetPressImage(SDL_Texture* image){
    if(image==nullptr)
        SDL_LogError(SDL_LOG_CATEGORY_RENDER, "image can't be nullptr");
    else
        press_image = image;
}

SDL_Texture* ImageButton::GetNormalImage(){
    return this->normal_image;
}

SDL_Texture* ImageButton::GetPressImage(){
    return this->press_image;
}
