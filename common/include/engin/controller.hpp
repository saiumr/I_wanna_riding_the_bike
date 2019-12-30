//
// Created by 桂明谦 on 2019/12/24.
//

#ifndef FARTRACE_CONTROLLER_HPP
#define FARTRACE_CONTROLLER_HPP

#include "SDL.h"
#include "spdlog/spdlog.h"

class Controller {
public:
    static Controller* GetController();
    static void SetController(Controller* cont);

    //在这里定义所有可操控按键
    enum Controller_Keys{
        CONTROLLER_TOGGLE_UP = 0,
        CONTROLLER_TOGGLE_DOWN,
        CONTROLLER_LEFT,
        CONTROLLER_RIGHT,
        CONTROLLER_JUMP,
        CONTROLLER_ESCAPE,
        CONTROLLER_ENTER,
        CONTROLLER_FULLSCREEN_TOGGLE,

        CONTROLLER_KEY_COUNT
    };

    Controller();
    bool Hold(Controller_Keys key);
    bool Pressed(Controller_Keys key);
    bool Released(Controller_Keys key);
    void SetKeyState(Controller_Keys key, bool ispress);
    virtual void EventHandle(SDL_Event& event) = 0;
    void Reset();
    void Update();
protected:
    bool key_map[CONTROLLER_KEY_COUNT];
    bool oldkey_map[CONTROLLER_KEY_COUNT];
private:
    static Controller* controller;
};


#endif //FARTRACE_CONTROLLER_HPP
