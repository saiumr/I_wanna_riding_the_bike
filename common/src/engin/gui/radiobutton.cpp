//
// Created by 桂明谦 on 2020/1/14.
//

#include "engin/gui/radiobutton.hpp"

#include <utility>

using namespace GUI;

//implement RadioButtonGroup
const RadioButton RadioButtonGroup::No_SelectedButton = RadioButton();

const int RadioButtonGroup::DefaultSelectedButton = 0;

RadioButtonGroup::RadioButtonGroup(vector<RadioButton> &items, int left, int top, int padding):GroupButtonGroup(left, top, padding){
    current_select = DefaultSelectedButton;
    for(RadioButton& button : items){
        button.id = current_free_item_id++;
        button.group = this;
        button.UnSelect();
        buttons.push_back(button);
    }
    buttons[current_select].Select();
}

void RadioButtonGroup::SelectButton(const int idx){
    buttons[current_select].UnSelect();
    current_select = idx;
    buttons[current_select].Select();
}

void RadioButtonGroup::Append(RadioButton radiobutton){
    radiobutton.id = current_free_item_id++;
    radiobutton.group = this;
    if(buttons.empty())
        radiobutton.Select();
    else
        radiobutton.UnSelect();
    buttons.push_back(radiobutton);
}

void RadioButtonGroup::Remove(ID id){
    for(int i=0;i<buttons.size();i++)
        if(buttons[i].GetID()==id) {
            if(buttons[current_select].GetID()==id)
                current_select = DefaultSelectedButton;
            buttons.erase(buttons.begin() + i);
        }
    if(current_select>=buttons.size())
        current_select = DefaultSelectedButton;
}

RadioButton RadioButtonGroup::GetSelectedButton() const{
    if(buttons.empty())
        return No_SelectedButton;
    return buttons[current_select];
}

vector<RadioButton> RadioButtonGroup::GetRadioButtons() const{
    return buttons;
}

RadioButton RadioButtonGroup::operator[](const int idx) const{
    if(idx>=buttons.size())
        return No_SelectedButton;
    return buttons[idx];
}

void RadioButtonGroup::EventHandle(SDL_Event& event){
    for(RadioButton& button : buttons)
        button.EventHandle(event);
}

void RadioButtonGroup::ClearAllState(){
    for(RadioButton& button : buttons)
        button.UnSelect();
}

void RadioButtonGroup::Update(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    FC_Font* font = FC_CreateFont();
    for(int i=0;i<buttons.size();i++) {
        FC_LoadFont(font, render, GUIResourceManager::GetTTFPath().c_str(), static_cast<int>(buttons[i].GetSize().h*2/3.0), buttons[i].GetForegroundColor(), TTF_STYLE_NORMAL);
        SDL_Point button_pos, font_pos;
        const char* text = buttons[i].GetText().c_str();
        SDL_Size font_size = {FC_GetWidth(font, text), FC_GetHeight(font, text)};
        CalculatePosition(i, button_pos, buttons[i].GetSize(), font_pos, font_size);
        buttons[i].Move(button_pos.x, button_pos.y);
        buttons[i].Update();
        FC_Draw(font, render, font_pos.x, font_pos.y, text);
    }
    FC_FreeFont(font);
}


//implement RadioButton
SDL_Color RadioButton::DefaultOutlineColor = {0, 200, 0, 255};
SDL_Color RadioButton::DefaultInnerColor = {200, 0, 0, 255};
int RadioButton::DefaultBoarderLen = 20;

RadioButton::RadioButton():selected(false),group(nullptr),outline_color(DefaultOutlineColor),inner_color(DefaultInnerColor){
    Resize(DefaultBoarderLen, DefaultBoarderLen);
}

RadioButton::RadioButton(string text):RadioButton(){
    this->text = std::move(text);
}

void RadioButton::Select(){
    selected = true;
}

void RadioButton::UnSelect(){
    selected = false;
}

bool RadioButton::IsSelected() const{
    return selected;
}

RadioButtonGroup* RadioButton::GetGroup() const{
    return group;
}

void RadioButton::SetOutlineColor(int r, int g, int b, int a){
    outline_color.r = r;
    outline_color.g = g;
    outline_color.b = b;
    outline_color.a = a;
}

SDL_Color RadioButton::GetOutlineColor() const{
    return outline_color;
}

void RadioButton::SetInnerColor(int r, int g, int b, int a){
    inner_color.r = r;
    inner_color.g = g;
    inner_color.b = b;
    inner_color.a = a;
}

SDL_Color RadioButton::GetInnerColor() const{
    return inner_color;
}

void RadioButton::EventHandle(SDL_Event& event){
    if(event.type==SDL_MOUSEBUTTONDOWN){
        SDL_Point mouse_pos = {event.button.x, event.button.y};
        SDL_Rect rrect = Rectf2Rect(&rect);
        if(SDL_PointInRect(&mouse_pos, &rrect)) {
            group->ClearAllState();
            selected = !selected;
        }
    }
}

bool RadioButton::QueryState(unsigned int s) const{
    switch(s){
        case SELECTED:
            return selected;
        case UNSELECTED:
            return !selected;
    }
    return false;
}

void RadioButton::draw(){
    SDL_Renderer* render = GUIResourceManager::GetRender();
    SDL_Color bgcolor = GetBackgroundColor();
    SDL_SetRenderDrawColor(render, bgcolor.r, bgcolor.g, bgcolor.b, bgcolor.a);
    SDL_Rect rrect = Rectf2Rect(&rect);
    SDL_RenderFillRect(render, &rrect);
    SDL_SetRenderDrawColor(render, outline_color.r, outline_color.g, outline_color.b, outline_color.a);
    SDL_RenderDrawRect(render, &rrect);
    if(selected){
        SDL_SetRenderDrawColor(render, inner_color.r, inner_color.g, inner_color.b, inner_color.a);
        const SDL_Size inner_padding = {static_cast<int>(GetSize().w*1/4.0), static_cast<int>(GetSize().h*1/4.0)};
        SDL_Rect inner_rect = {rrect.x+inner_padding.w, rrect.y+inner_padding.h, rrect.w-inner_padding.w*2, rrect.h-inner_padding.h*2};
        SDL_RenderFillRect(render, &inner_rect);
    }
}
