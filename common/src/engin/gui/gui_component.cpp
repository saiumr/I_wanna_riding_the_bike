//
// Created by 桂明谦 on 2020/1/6.
//

#include "engin/gui/gui_component.hpp"

using namespace GUI;

GUIComponent::GUIComponent():Object(),visiable(true),image(nullptr){}

GUIComponent::GUIComponent(int x, int y, int w, int h):Object(x, y, w, h),visiable(false),image(nullptr){}

bool GUIComponent::IsVisiable() const{
    return visiable;
}

void GUIComponent::Show(){
    visiable = true;
}

void GUIComponent::Hide(){
    visiable = false;
}

void GUIComponent::Update(){
    update();
    if(visiable)
        draw();
}
