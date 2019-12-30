#ifndef __STAGE_HPP__
#define __STAGE_HPP__
#include "director.hpp"
#include "controller.hpp"
#include "SDL.h"

class Stage{
public:
    static void Run();
private:
    Stage() = delete;
    Stage(Stage& other) = delete;
    Stage& operator=(const Stage& other) = delete;
    static void eventHandle();
    static SDL_Event event;
    static void controllerUpdate();
};
#endif