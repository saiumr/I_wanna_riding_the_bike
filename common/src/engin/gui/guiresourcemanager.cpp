//
// Created by 桂明谦 on 2020/1/6.
//

#include "engin/gui/guiresourcemanager.hpp"

using namespace GUI;

string GUIResourceManager::ttf_path = "resources/Fangsong.ttf";
SDL_Renderer* GUIResourceManager::render = nullptr;

void GUIResourceManager::InitGUI(SDL_Renderer* render){
    GUIResourceManager::render = render;
}

string GUIResourceManager::GetTTFPath(){
    return ttf_path;
}

SDL_Renderer* GUIResourceManager::GetRender(){
    return render;
}
