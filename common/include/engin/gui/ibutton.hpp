//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP

#include "gui_component.hpp"
#include <string>
using namespace std;

class IButton:public GUIComponent{
public:
    enum State{
        PRESSED,
        NORMAL
    };
    IButton();
    IButton(int x, int y, int w, int h);
    void SetText(const string text);
    string GetText();
    void EventHandle(SDL_Event& event) override;
    void SetCallBack_ButtonPress(ButtonPress_CallBack ncallback);
    void SetCallBack_ButtonRelease(ButtonRelease_CallBack ncallback);
    void SetCallBack_MouseMove(MouseMove_CallBack ncallback);
    void SetCallBack_Click(Click_CallBack ncallback);
    State GetState();
protected:
    Click_CallBack clickCallBack;
    ButtonPress_CallBack buttonPressCallBack;
    ButtonRelease_CallBack buttonReleaseCallBack;
    MouseMove_CallBack mouseMoveCallBack;
    State state;
    string text;
private:
    bool button_pressed;
};

#endif //I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP
