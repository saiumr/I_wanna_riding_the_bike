//
// Created by 桂明谦 on 2019/12/24.
//

#ifndef FARTRACE_KEYBOARDCONTROLLER_HPP
#define FARTRACE_KEYBOARDCONTROLLER_HPP

#include "engin/controller.hpp"
#include "controllers/keyboard_config.hpp"

class KeyboardController: public Controller {
public:
    KeyboardController();
    KeyboardController(KeyboardConfig newconfig);
    void EventHandle(SDL_Event& event) override;
private:
    KeyboardConfig config;
};

#endif //FARTRACE_KEYBOARDCONTROLLER_HPP
