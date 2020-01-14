//
// Created by 桂明谦 on 2020/1/14.
//

#ifndef I_WANNA_RIDING_THE_BIKE_SLIDEBAR_HPP
#define I_WANNA_RIDING_THE_BIKE_SLIDEBAR_HPP

#include <sstream>
#include "gui_component.hpp"
#include "guiresourcemanager.hpp"
using namespace std;

namespace GUI{

    class SlideBar:public GUIComponent {
    public:
        enum class Type{
            VERTICAL,
            HORIZONTAL
        };
        static const int DefaultLen;
        static const Type DefaultType;
        static const SDL_Size ButtonSize;
        SlideBar(int minvalue, int maxvalue, int length=DefaultLen, Type t=DefaultType);
        Type GetType() const;
        void SetType(Type t);
        float GetValue() const;
        void SetValue(float v);
        float GetMinValue() const;
        float GetMaxValue() const;
        void SetMinValue(float v);
        void SetMaxValue(float v);
        void EventHandle(SDL_Event& event) override;
        void Resize(int len);
        bool QueryState(unsigned int s) const override;
    protected:
        Type type;
        int len;
        float min_value;
        float max_value;
        float value;
        bool button_pressed;

        void draw() override;
        void drawText();
        void drawButton();
        void drawBar();
        void update() override;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_SLIDEBAR_HPP
