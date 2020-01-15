//
// Created by 桂明谦 on 2020/1/14.
//

#ifndef I_WANNA_RIDING_THE_BIKE_MESSAGEBOX_HPP
#define I_WANNA_RIDING_THE_BIKE_MESSAGEBOX_HPP

#include "guiresourcemanager.hpp"
#include "engin/mmath.hpp"
#include <vector>

using namespace std;

namespace GUI {

    enum class ResultType{
        OK,
        CANCEL,
        YES,
        NO
    };
    enum class ButtonType{
        YES_NO,
        OK_CANCEL,
    };

    struct MsgButton{
        string text;
        unsigned int resultID;
    };

    ResultType ShowMessageBox(SDL_Point pos, SDL_Size size, ButtonType buttontype, string title, string content);
    //unsigned int ShowUserMessageBox(SDL_Point pos, SDL_Size size, vector<MsgButton> buttons, string title, string content);

}

#endif //I_WANNA_RIDING_THE_BIKE_MESSAGEBOX_HPP
