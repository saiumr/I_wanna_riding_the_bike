//
// Created by 桂明谦 on 2020/1/6.
//

#include "guitestframework.hpp"
#include "engin/gui/guiresourcemanager.hpp"
#include "engin/gui/button.hpp"

class GUI_Test:public GUITestframework{
public:
    GUI_Test():GUITestframework("GUI components", 800, 600, SDL_WINDOW_SHOWN){
        GUIResourceManager::InitGUI(render);
        button.SetText("button1");
        button.Move(100, 200);
        button.Resize(100, 60);
        button.SetCallBack_Click([](SDL_MouseButtonEvent& event){
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "button clicked");
        });
    }

    void EventHandle(SDL_Event& event) override{
        GUITestframework::EventHandle(event);
        button.EventHandle(event);
    }

    void Update() override{
        button.Update();
    }
private:
    Button button;
};

RUN_APP(GUI_Test)
