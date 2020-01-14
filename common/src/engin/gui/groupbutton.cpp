//
// Created by 桂明谦 on 2020/1/14.
//

#include "engin/gui/groupbutton.hpp"

using namespace GUI;

const int GroupButtonGroup::DEFAULT_PADDING = 10;

GroupButtonGroup::GroupButtonGroup():current_free_item_id(1),padding(DEFAULT_PADDING),textWarpType(TextWarpType::RIGHT),itemAlignType(ItemAlignType::VERTICAL){}

GroupButtonGroup::GroupButtonGroup(int left, int right, int padding):GroupButtonGroup(){
    SetTopLeft(left, right);
    this->padding = padding;
}

int GroupButtonGroup::GetPadding(){
    return padding;
}

void GroupButtonGroup::SetPadding(int padding){
    this->padding = padding;
}

void GroupButtonGroup::SetItemAlignType(ItemAlignType type){
    itemAlignType = type;
}

void GroupButtonGroup::SetTextWarpType(TextWarpType type){
    textWarpType = type;
}

GroupButtonGroup::ItemAlignType GroupButtonGroup::GetItemAlignType(){
    return itemAlignType;
}

GroupButtonGroup::TextWarpType GroupButtonGroup::GetTextWarpType(){
    return textWarpType;
}

void GroupButtonGroup::SetTopLeft(int x, int y){
    tl.x = x;
    tl.y = y;
}

SDL_Point GroupButtonGroup::GetTopLeft() const{
    return tl;
}

void GroupButtonGroup::CalculatePosition(int idx, SDL_Point& button_pos, SDL_Size button_size, SDL_Point& font_pos, SDL_Size font_size){
    switch(itemAlignType){
        case ItemAlignType::VERTICAL:
            button_pos.x = tl.x;
            button_pos.y = tl.y+idx*(button_size.h+padding);
            break;
        case ItemAlignType::HORIZONTAL:
            button_pos.x = tl.x+idx*(button_size.w+padding);
            button_pos.y = tl.y;
            break;
    }
    switch(textWarpType){
        case TextWarpType::TOP:
            font_pos.x = button_pos.x+button_size.w/2-font_size.w/2;
            font_pos.y = button_pos.y-font_size.h;
            break;
        case TextWarpType::BUTTOM:
            font_pos.x = button_pos.x+button_size.w/2-font_size.w/2;
            font_pos.y = button_pos.y+button_size.h;
            break;
        case TextWarpType::LEFT:
            font_pos.x = button_pos.x - font_size.w;
            font_pos.y = button_pos.y+button_size.h/2-font_size.h/2;
            break;
        case TextWarpType::RIGHT:
            font_pos.x = button_pos.x + button_size.w;
            font_pos.y = button_pos.y+button_size.h/2-font_size.h/2;
            break;
    }
}

//GroupButton implements
GroupButton::GroupButton():id(ERROR_ID){}

GroupButton::GroupButton(ID nid):id(nid){}

ID GroupButton::GetID() const{
    return id;
}
