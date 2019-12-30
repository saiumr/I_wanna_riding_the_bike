//
// Created by 桂明谦 on 2019/12/25.
//

#ifndef FARTRACE_KEYBOARDCONFIG_HPP
#define FARTRACE_KEYBOARDCONFIG_HPP

#include "engin/controller.hpp"
#include <map>
using namespace std;

class KeyboardConfig {
public:
    using KeyMap = map<unsigned int, Controller::Controller_Keys>;
    //使用默认构造函数来获得默认的按键设置
    KeyboardConfig();
    //使用这个函数更改默认键位
    void BindKey(unsigned int key, Controller::Controller_Keys controllerKeys);
    KeyMap& GetKeyMap();
private:
    KeyMap key_bind;
};


#endif //FARTRACE_KEYBOARDCONFIG_HPP
