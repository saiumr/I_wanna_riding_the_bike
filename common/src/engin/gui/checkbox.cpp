//
// Created by 桂明谦 on 2020/1/10.
//

#include "engin/gui/checkbox.hpp"

using namespace GUI;

//CheckBoxGroup implements

ID CheckBoxGroup::current_free_group_id = 1;

const int CheckBoxGroup::DEFAULT_PADDING = 10;

CheckBoxGroup::CheckBoxGroup():id(current_free_group_id++),current_free_item_id(1),padding(DEFAULT_PADDING),textWarpType(TextWarpType::RIGHT),itemAlignType(ItemAlignType::VERTICAL){}

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

int CheckBoxGroup::GetPadding(){
    return padding;
}

void CheckBoxGroup::SetPadding(int padding){
    this->padding = padding;
}

void CheckBoxGroup::SetItemAlignType(ItemAlignType type){
    itemAlignType = type;
}

void CheckBoxGroup::SetTextWarpType(TextWarpType type){
    textWarpType = type;
}

CheckBoxGroup::ItemAlignType CheckBoxGroup::GetItemAlignType(){
    return itemAlignType;
}

CheckBoxGroup::TextWarpType CheckBoxGroup::GetTextWarpType(){
    return textWarpType;
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

ID CheckBoxGroup::GetID() const{
    return id;
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

void CheckBoxGroup::SetTopLeft(int x, int y){
    tl.x = x;
    tl.y = y;
}

SDL_Point CheckBoxGroup::GetTopLeft() const{
    return tl;
}

void CheckBoxGroup::Update(){
    SDL_Size font_size;
    SDL_Point box_pos = GetTopLeft(), font_pos;
    SDL_Renderer* render = GUIResourceManager::GetRender();
    for(CheckBox& box : items) {
        FC_Font* font = FC_CreateFont();
        FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), box.GetSize().h*2/3.0, box.GetForegroundColor(), TTF_STYLE_NORMAL);
        string text = box.GetText();
        font_size.h = FC_GetHeight(font, text.c_str());
        font_size.w = FC_GetWidth(font, text.c_str());
        SDL_Size box_size = box.GetSize();
        switch(textWarpType){
            case TextWarpType::TOP:
                font_pos.y = box_pos.y-font_size.h;
                font_pos.x = box_pos.x+box_size.w/2-font_size.w/2;
                break;
            case TextWarpType::RIGHT:
                font_pos.x = box_pos.x+box_size.w;
                font_pos.y = box_pos.y+box_size.h/2-font_size.h/2;
                break;
            case TextWarpType::LEFT:
                font_pos.x = box_pos.x-font_size.w;
                font_pos.y = box_pos.y+box_size.h/2-font_size.h/2;
                break;
            case TextWarpType::BUTTOM:
                font_pos.y = box_pos.y+box_size.h;
                font_pos.x = box_pos.x+box_size.w/2-font_size.w/2;
                break;
        }

        box.Move(box_pos.x, box_pos.y);
        box.Update();
        if(font)
            FC_Draw(font, render, font_pos.x, font_pos.y, text.c_str());
        else
            SDL_LogError(SDL_LOG_CATEGORY_RENDER, "font not fount");
        FC_FreeFont(font);

        switch(itemAlignType){
            case ItemAlignType::VERTICAL:
                switch(textWarpType){
                    case TextWarpType::TOP:
                    case TextWarpType::BUTTOM:
                        box_pos.y = box_pos.y+box_size.h+font_size.h+padding;
                        break;
                    case TextWarpType::LEFT:
                    case TextWarpType::RIGHT:
                        box_pos.y = box_pos.y+box_size.w+padding;
                        break;
                }
                break;
            case ItemAlignType::HORIZONTAL:
                switch(textWarpType){
                    case TextWarpType::LEFT:
                    case TextWarpType::RIGHT:
                        box_pos.x = box_pos.x+box_size.w+font_size.w+padding;
                        break;
                    case TextWarpType::TOP:
                    case TextWarpType::BUTTOM:
                        box_pos.x = box_pos.x+box_size.w/2+(box_size.w>font_size.w?box_size.w/2:font_size.w-box_size.w/2)+padding;
                        break;
                }
                break;
        }
    }
}

//CheckBox implements

const int CheckBox::default_len = 20;

CheckBox::CheckBox():group(nullptr),id(ERROR_ID),checked(false),boxcolor({0, 150, 0, 255}),rightcolor({200, 0, 0, 255}){
    Resize(default_len, default_len);
}

CheckBox::CheckBox(string text):CheckBox(){
    this->text = text;
}

CheckBox::CheckBox(string text, bool checked):CheckBox(checked){
    this->text = text;
}

CheckBox::CheckBox(bool ischeck):group(nullptr),checked(ischeck),id(ERROR_ID),boxcolor({0, 150, 0, 255}),rightcolor({200, 0, 0, 255}){
    Resize(default_len, default_len);
}

void CheckBox::Check(){
    checked = true;
}
void CheckBox::Uncheck(){
    checked = false;
}

ID CheckBox::GetID(){
    return id;
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

bool CheckBox::QueryState(unsigned int s){
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
    SDL_SetRenderDrawColor(render, 100, 100, 100, boxcolor.a);
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
