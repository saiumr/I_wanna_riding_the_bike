//
// Created by 桂明谦 on 2020/1/14.
//

#ifndef I_WANNA_RIDING_THE_BIKE_RADIOBUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_RADIOBUTTON_HPP

#include "groupbutton.hpp"

namespace GUI{

    class RadioButton;

    class RadioButtonGroup:public GroupButtonGroup{
    public:
        static const RadioButton No_SelectedButton;
        static const int DefaultSelectedButton;
        RadioButtonGroup() = default;
        RadioButtonGroup(vector<RadioButton> &items, int left, int top, int padding=DEFAULT_PADDING);
        void Append(RadioButton radiobutton);
        void Remove(ID id);
        RadioButton GetSelectedButton() const;
        void SelectButton(const int idx);
        vector<RadioButton> GetRadioButtons() const;
        RadioButton operator[](const int idx) const;
        void ClearAllState();
        void EventHandle(SDL_Event& event);
        void Update() override ;
    private:
        vector<RadioButton> buttons;
        int current_select;
    };

    class RadioButton:public GroupButton{
    public:
        friend class RadioButtonGroup;
        static SDL_Color DefaultOutlineColor;
        static SDL_Color DefaultInnerColor;
        static int DefaultBoarderLen;
        enum State{
            SELECTED,
            UNSELECTED
        };
        RadioButton();
        explicit RadioButton(string text);
        void Select();
        void UnSelect();
        bool IsSelected() const;
        RadioButtonGroup* GetGroup() const;
        void SetOutlineColor(int r, int g, int b, int a=255);
        SDL_Color GetOutlineColor() const;
        void SetInnerColor(int r, int g, int b, int a=255);
        SDL_Color GetInnerColor() const;
        void EventHandle(SDL_Event& event) override;
        bool QueryState(unsigned int s) const override;
    protected:
        bool selected;
        RadioButtonGroup* group;
        SDL_Color outline_color;
        SDL_Color inner_color;

        void draw() override;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_RADIOBUTTON_HPP
