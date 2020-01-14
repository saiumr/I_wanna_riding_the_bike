//
// Created by 桂明谦 on 2020/1/10.
//

#include "engin/gui/checkbox.hpp"

#include <utility>

using namespace GUI;

//CheckBoxGroup implements

CheckBoxGroup::CheckBoxGroup(vector<CheckBox> &items, int left, int right, int padding):CheckBoxGroup(){
    for(CheckBox& box : items)
        box.id = current_free_item_id++;
    this->padding = DEFAULT_PADDING;
}

vector<CheckBox> CheckBoxGroup::GetCheckedItems() const{
    vector<CheckBox> boxes;
    boxes.clear();
    for(CheckBox box : items)
        if(box.IsChecked())
            boxes.push_back(box);
    return boxes;
}

void CheckBoxGroup::EventHandle(SDL_Event& event){
    for(CheckBox& box : items)
        box.EventHandle(event);
}

void CheckBoxGroup::Append(CheckBox checkbox){
    checkbox.id = current_free_item_id++;
    checkbox.group = this;
    items.push_back(checkbox);
}

void CheckBoxGroup::remove(ID id){
    for(int i=0;i<items.size();i++)
        if(items[i].GetID()==id)
            items.erase(items.begin()+i);
}

vector<CheckBox> CheckBoxGroup::GetItems() const{
    return items;
}

CheckBox CheckBoxGroup::operator[](int idx) const{
    return items[idx];
}

void CheckBoxGroup::Update(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    FC_Font* font = FC_CreateFont();
    for(int i=0;i<items.size();i++) {
        FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), static_cast<int>(items[i].GetSize().h*2/3.0), items[i].GetForegroundColor(), TTF_STYLE_NORMAL);
        SDL_Point button_pos, font_pos;
        const char* text = items[i].GetText().c_str();
        SDL_Size font_size = {FC_GetWidth(font, text), FC_GetHeight(font, text)};
        CalculatePosition(i, button_pos, items[i].GetSize(), font_pos, font_size);
        items[i].Move(button_pos.x, button_pos.y);
        items[i].Update();
        FC_Draw(font, render, font_pos.x, font_pos.y, text);
    }
    FC_FreeFont(font);
}

//CheckBox implements

const int CheckBox::default_len = 20;

CheckBox::CheckBox():group(nullptr),checked(false),boxcolor({0, 150, 0, 255}),rightcolor({200, 0, 0, 255}){
    Resize(default_len, default_len);
}

CheckBox::CheckBox(string text):CheckBox(){
    this->text = std::move(text);
}

CheckBox::CheckBox(string text, bool checked):CheckBox(checked){
    this->text = std::move(text);
}

CheckBox::CheckBox(bool ischeck):group(nullptr),checked(ischeck),boxcolor({0, 150, 0, 255}),rightcolor({200, 0, 0, 255}){
    Resize(default_len, default_len);
}

void CheckBox::Check(){
    checked = true;
}
void CheckBox::Uncheck(){
    checked = false;
}

bool CheckBox::IsChecked() const{
    return checked;
}

void CheckBox::EventHandle(SDL_Event& event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        SDL_Point mouse_pos = {event.button.x, event.button.y};
        if(SDL_PointInRect(&mouse_pos, &rect))
            checked = !checked;
    }
}

void CheckBox::SetRightColor(SDL_Color color){
    rightcolor.r = color.r;
    rightcolor.g = color.g;
    rightcolor.b = color.b;
    rightcolor.a = color.a;
}

void CheckBox::SetBoxColor(SDL_Color color){
    boxcolor.r = color.r;
    boxcolor.g = color.g;
    boxcolor.b = color.b;
    boxcolor.a = color.a;
}

SDL_Color CheckBox::GetRightColor() const{
    return rightcolor;
}

SDL_Color CheckBox::GetBoxColor() const{
    return boxcolor;
}

CheckBoxGroup* CheckBox::GetGroup() const{
    return group;
}

bool CheckBox::QueryState(unsigned int s) const{
    switch(s){
        case CHECKED:
            return true;
        case UNCHECKED:
            return false;
    }
    return false;
}

void CheckBox::draw(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    //Draw Box
    SDL_Color bgcolor = GetBackgroundColor();
    SDL_SetRenderDrawColor(render, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
    SDL_RenderFillRect(render, &rect);
    SDL_SetRenderDrawColor(render, boxcolor.r, boxcolor.g, boxcolor.b, boxcolor.a);
    SDL_RenderDrawRect(render, &rect);
    //Draw right shape
    if(checked){
        SDL_SetRenderDrawColor(render, rightcolor.r, rightcolor.g, rightcolor.b, rightcolor.a);
        SDL_Point p1 = {rect.x+rect.w/4, rect.y+rect.h/2},
                  p2 = {rect.x+rect.w/2, static_cast<int>(rect.y+rect.h*7/8.0)},
                  p3 = {static_cast<int>(rect.x+rect.w*7/8.0), static_cast<int>(rect.y+rect.h/8.0)};
        SDL_RenderDrawLine(render, p1.x, p1.y, p2.x, p2.y);
        SDL_RenderDrawLine(render, p2.x, p2.y, p3.x, p3.y);
    }
}
