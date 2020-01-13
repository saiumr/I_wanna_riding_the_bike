//
// Created by 桂明谦 on 2020/1/10.
//

#ifndef I_WANNA_RIDING_THE_BIKE_IMAGEBUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_IMAGEBUTTON_HPP

#include "engin/gui/ibutton.hpp"

namespace GUI {

    class ImageButton : public IButton {
    public:
        ImageButton() = default;
        ImageButton(int x, int y, SDL_Texture *normal, SDL_Texture *press, float scalex = 1, float scaly = 1);
        void SetImage(SDL_Texture *normal, SDL_Texture *press);
        void SetNormalImage(SDL_Texture *image);
        void SetPressImage(SDL_Texture *image);
        SDL_Texture *GetNormalImage();
        SDL_Texture *GetPressImage();
    private:
        void draw() override;
        SDL_Texture *normal_image;
        SDL_Texture *press_image;
        float scalex;
        float scaley;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_IMAGEBUTTON_HPP
