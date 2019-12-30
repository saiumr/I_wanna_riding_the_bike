//
// Created by 桂明谦 on 2019/12/24.
//

#include "controllers/keyboardcontroller.hpp"

KeyboardController::KeyboardController(){}

KeyboardController::KeyboardController(KeyboardConfig newconfig):config(newconfig){}

void KeyboardController::EventHandle(SDL_Event& event){
    unsigned int keysym = static_cast<int>(event.key.keysym.sym);
    KeyboardConfig::KeyMap& keymap = config.GetKeyMap();
    if(event.type == SDL_KEYDOWN){
        if(keymap.find(keysym)!=keymap.end()){
            key_map[keymap[keysym]] = true;
        }
    }
    if(event.type == SDL_KEYUP){
        if(keymap.find(keysym)!=keymap.end()){
            key_map[keymap[keysym]] = false;
        }
    }
}
