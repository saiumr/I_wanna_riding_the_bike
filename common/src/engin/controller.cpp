//
// Created by 桂明谦 on 2019/12/24.
//

#include "engin/controller.hpp"

Controller* Controller::controller = nullptr;

Controller* Controller::GetController(){
    if(controller==nullptr)
        spdlog::error("no controller");
    return controller;
}

void Controller::SetController(Controller* cont){
    controller = cont;
}

Controller::Controller(){
    Reset();
}

bool Controller::Hold(Controller_Keys key){
    return oldkey_map[key] && key_map[key];
}

bool Controller::Pressed(Controller_Keys key){
    return !oldkey_map[key] && key_map[key];
}

bool Controller::Released(Controller_Keys key){
    return oldkey_map[key] && !key_map[key];
}

void Controller::SetKeyState(Controller_Keys key, bool ispress){
    key_map[key] = ispress;
}

//如果加了新的按键，需要在这里初始化为false
void Controller::Reset(){
    for(int i=0;i<CONTROLLER_KEY_COUNT;i++) {
        key_map[i] = false;
        oldkey_map[i] = false;
    }
}

void Controller::Update(){
    for(int i=0;i<CONTROLLER_KEY_COUNT;i++)
        oldkey_map[i] = key_map[i];
}
