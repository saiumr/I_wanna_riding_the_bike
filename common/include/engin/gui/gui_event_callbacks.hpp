//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_GUI_EVENT_CALLBACKS_HPP
#define I_WANNA_RIDING_THE_BIKE_GUI_EVENT_CALLBACKS_HPP

#include "SDL.h"
#include <functional>
using namespace std;

using Click_CallBack = function<void(SDL_MouseButtonEvent&)>;
using ButtonPress_CallBack = function<void(SDL_MouseButtonEvent&)>;
using ButtonRelease_CallBack = function<void(SDL_MouseButtonEvent&)>;
using MouseMove_CallBack = function<void(SDL_MouseMotionEvent&)>;
using KeyPress_CallBack = function<void(SDL_KeyboardEvent&)>;
using KeyRelease_CallBack = function<void(SDL_KeyboardEvent&)>;

#endif //I_WANNA_RIDING_THE_BIKE_GUI_EVENT_CALLBACKS_HPP
