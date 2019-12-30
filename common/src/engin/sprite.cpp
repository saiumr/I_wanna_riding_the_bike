//
// Created by 桂明谦 on 2019/12/19.
//

#include "engin/sprite.hpp"

Sprite::Sprite():isshow(true),flip(NO_FLIP){}

Sprite::Sprite(int x, int y, string image_name):Object(x, y, 0, 0),isshow(true),flip(NO_FLIP){
    image = ImageEntrepot::GetImage(image_name);
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    Resize(w, h);
}

Sprite_Image* Sprite::GetImage(){
    return image;
}

void Sprite::SuitSize(){
    if(image== nullptr){
        cerr<<"Sprite::SuitSize(): can't suit size because image==nullptr";
        return;
    }
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    Resize(w, h);
}

void Sprite::Flip(Flip_Flag flag){
    flip = flag;
}

bool Sprite::IsFlip(){
    return flip;
}

void Sprite::Show(){
    isshow = true;
}

void Sprite::Hide(){
    isshow = false;
}

bool Sprite::IsVisiable(){
    return isshow;
}

void Sprite::SetImage(string name){
    image = ImageEntrepot::GetImage(name);
    SuitSize();
}

SDL_Point Sprite::GetOriginalSize(){
    int w, h;
    SDL_QueryTexture(image, nullptr, nullptr, &w, &h);
    return {w, h};
}

void Sprite::Draw(){
    if(isshow) {
        Point position = GetPosition();
        SDL_Size size = GetSize();
        SDL_RendererFlip flip_flag = (flip==FLIP?SDL_FLIP_HORIZONTAL:SDL_FLIP_NONE);
        SDL_Rect dstrect = {static_cast<int>(position.x - size.w*anchor.x), static_cast<int>(position.y-size.h*anchor.y), size.w, size.h};
        SDL_RenderCopyEx(Director::GetDirector()->GetRender(), image, nullptr, &dstrect, angle, nullptr, flip_flag);
    }
}

void Sprite::step(){}

void Sprite::Update(){
    step();
    Draw();
}
