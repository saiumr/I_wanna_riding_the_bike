//
// Created by 桂明谦 on 2020/1/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_BUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_BUTTON_HPP

#include "ibutton.hpp"


class Button:public IButton{
public:
    Button();
    Button(const string text, int x, int y, int w, int h);
    void SetForegroundColor(int r, int g, int b, int a=255);
    void SetBackgroundColor(int r, int g, int b, int a=255);
private:
    static SDL_Color dark_cover;
    void draw() override;
    void update() override;
    SDL_Color foregroundColor;
    SDL_Color backgroundColor;
};

#endif //I_WANNA_RIDING_THE_BIKE_BUTTON_HPP
