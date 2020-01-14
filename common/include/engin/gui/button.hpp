//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_BUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_BUTTON_HPP

#include "ibutton.hpp"

namespace GUI {
    class Button : public IButton {
    public:
        Button();
        Button(string text, int x, int y, int w, int h);
        void SetBackgroundColor(int r, int g, int b, int a = 255);
        SDL_Color GetBackgroundColor() const;
    protected:
        void draw() override;
        SDL_Color foregroundColor;
        SDL_Color backgroundColor;
    };
}

#endif //I_WANNA_RIDING_THE_BIKE_BUTTON_HPP
