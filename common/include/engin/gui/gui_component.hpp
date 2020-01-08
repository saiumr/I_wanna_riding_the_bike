//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_GUI_COMPONENT_HPP
#define I_WANNA_RIDING_THE_BIKE_GUI_COMPONENT_HPP

#include "engin/object.hpp"
#include "gui_event_callbacks.hpp"
#include "guiresourcemanager.hpp"

class GUIComponent:public Object {
public:
    GUIComponent();
    GUIComponent(int x, int y, int w, int h);
    bool IsVisiable();
    void Show();
    void Hide();
    virtual void EventHandle(SDL_Event& event) = 0;
    void Update();
protected:
    virtual void draw() = 0;
    virtual void update() = 0;
    SDL_Texture* image;
private:
    bool visiable;
};

#endif //I_WANNA_RIDING_THE_BIKE_GUI_COMPONENT_HPP
