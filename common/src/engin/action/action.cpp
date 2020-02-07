//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/action.hpp"

Action::Action():time(0),current_time(0),isplaying(false){}

void Action::Play(){
    isplaying = true;
}

void Action::Stop(){
    isplaying = false;
    current_time = 0;
}

void Action::Pause(){
    isplaying = false;
}

string Action::GetName() {
    return name;
}

void Action::SetName(string name){
    this->name = name;
}

bool Action::IsPlaying(){
    return isplaying;
}
