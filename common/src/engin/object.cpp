//
// Created by 桂明谦 on 2019/12/19.
//

#include "engin/object.hpp"

Object::Object():rect({0, 0, 0, 0}),angle(0),anchor({0.5, 0.5}){}

Object::Object(int x, int y, int w, int h):rect({x, y, w, h}),angle(0),anchor({0.5, 0.5}){}

Point Object::GetPosition(){
    return {static_cast<int>(rect.x+anchor.x*rect.w), static_cast<int>(rect.y+anchor.y*rect.h)};
}

SDL_Size Object::GetSize(){
    return {rect.w, rect.h};
}

void Object::Move(int x, int y){
    rect.x = x;
    rect.y = y;
}

void Object::Resize(int w, int h){
    if(w<0 || h<0){
        spdlog::warn("Object::Resize: must w,h>=0");
        return ;
    }
    rect.w = w;
    rect.h = h;
}

void Object::Translate(int delta_x, int delta_y){
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

void Object::SetAnchorByPixel(float x, float y){
    anchor.x = x/rect.w;
    anchor.y = y/rect.h;
}

void Object::Scale(float scale_x, float scale_y){
    if((scale_x<0 && scale_x>1) || (scale_y<0 && scale_y>1)){
        spdlog::warn("Object::Scale: must 0<=scale_x, scale_y<=1");
        return ;
    }
    rect.w *= scale_x;
    rect.h *= scale_y;
}
