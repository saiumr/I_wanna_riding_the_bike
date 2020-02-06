//
// Created by 桂明谦 on 2019/12/19.
//

#include "engin/object.hpp"

Object::Object():rect({0, 0, 0, 0}),angle(0),anchor({0.5, 0.5}){}

Object::Object(float x, float y, int w, int h):rect({x, y, static_cast<float>(w), static_cast<float>(h)}),angle(0),anchor({0.5, 0.5}){}

Pointf Object::GetPosition(){
    return {rect.x+anchor.x*rect.w, rect.y+anchor.y*rect.h};
}

Point Object::GetIntPosition(){
    return {static_cast<int>(rect.x+anchor.x*rect.w), static_cast<int>(rect.y+anchor.y*rect.h)};
}

SDL_Size Object::GetSize(){
    return {static_cast<int>(rect.w), static_cast<int>(rect.h)};
}

void Object::Move(float x, float y){
    rect.x = x;
    rect.y = y;
}

void Object::Resize(int w, int h){
    if(w<0 || h<0){
        SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, "Object::Resize: must w,h>=0");
        return ;
    }
    rect.w = w;
    rect.h = h;
}

void Object::Translate(float delta_x, float delta_y){
    rect.x += delta_x;
    rect.y += delta_y;
}

float Object::GetDegree(){
    return angle;
}

void Object::RotateTo(float degree){
    angle = degree;
}

void Object::RotateDelta(float delta_degree){
    angle += delta_degree;
}

Pointf Object::GetAnchor(){
    return anchor;
}

void Object::SetAnchorByPercent(float x, float y){
    anchor.x = x;
    anchor.y = y;
}

void Object::SetAnchorByPixel(int x, int y){
    anchor.x = x/rect.w;
    anchor.y = y/rect.h;
}

void Object::Scale(float scale_x, float scale_y){
    if((scale_x<0 && scale_x>1) || (scale_y<0 && scale_y>1)){
        SDL_LogWarn(SDL_LOG_CATEGORY_CUSTOM, "Object::Scale: must 0<=scale_x, scale_y<=1");
        return ;
    }
    rect.w *= scale_x;
    rect.h *= scale_y;
}
