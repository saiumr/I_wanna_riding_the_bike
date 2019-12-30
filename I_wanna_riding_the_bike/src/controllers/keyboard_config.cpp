//
// Created by 桂明谦 on 2019/12/25.
//

#include "controllers/keyboard_config.hpp"

KeyboardConfig::KeyboardConfig(){
    key_bind[SDLK_w] = Controller::CONTROLLER_TOGGLE_UP;
    key_bind[SDLK_s] = Controller::CONTROLLER_TOGGLE_DOWN;
    key_bind[SDLK_a] = Controller::CONTROLLER_LEFT;
    key_bind[SDLK_d] = Controller::CONTROLLER_RIGHT;
    key_bind[SDLK_k] = Controller::CONTROLLER_JUMP;
    key_bind[SDLK_ESCAPE] = Controller::CONTROLLER_ESCAPE;
    key_bind[SDLK_KP_ENTER] = Controller::CONTROLLER_ENTER;
    key_bind[SDLK_F1] = Controller::CONTROLLER_FULLSCREEN_TOGGLE;
}

void KeyboardConfig::BindKey(unsigned int key, Controller::Controller_Keys controllerKeys){
    if(key_bind.find(key)==key_bind.end())
        cerr<<"no key";
    else
        key_bind[key] = controllerKeys;
}

KeyboardConfig::KeyMap& KeyboardConfig::GetKeyMap(){
    return key_bind;
}
