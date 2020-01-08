//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_GUIRESOURCEMANAGER_HPP
#define I_WANNA_RIDING_THE_BIKE_GUIRESOURCEMANAGER_HPP

#include "SDL.h"
#include "SDL_FontCache.h"
#include <string>
using namespace std;

class GUIResourceManager {
public:
    static void InitGUI(SDL_Renderer* render);
    static SDL_Renderer* GetRender();
    static string GetTTFPath();
private:
    static string ttf_path;
    static SDL_Renderer* render;
};


#endif //I_WANNA_RIDING_THE_BIKE_GUIRESOURCEMANAGER_HPP
