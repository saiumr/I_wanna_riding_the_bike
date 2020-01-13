//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP

#include "gui_component.hpp"
#include "guiheader.hpp"
#include <string>
using namespace std;

namespace GUI{

    class IButton : public GUIComponent {
    public:
        enum State{
            PRESSED,
            RELEASED,
            PRESSING,
            MOUSE_MOVING,
            NORMAL
        };
        IButton();
        IButton(int x, int y, int w, int h);
        void SetText(const string text);
        string GetText();
        void EventHandle(SDL_Event &event) override;
        SDL_Color GetForegroundColor();
        void SetForegroundColor(int r, int g, int b, int a = 255);
        bool QueryState(unsigned int s) override;
    protected:
        SDL_Color fgcolor;
        string text;
        static SDL_Color dark_cover;
        void update() override;
    private:
        bool button_pressed;
        bool old_button_pressed;
        bool mouse_moved;
    };
}

#endif //I_WANNA_RIDING_THE_BIKE_IBUTTON_HPP
