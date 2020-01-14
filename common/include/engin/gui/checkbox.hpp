//
// Created by 桂明谦 on 2020/1/10.
//

#ifndef I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP
#define I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP

#include "groupbutton.hpp"
#include <vector>
using namespace std;

namespace GUI {

    class CheckBox;

    class CheckBoxGroup:public GroupButtonGroup {
    public:
        CheckBoxGroup() = default;
        CheckBoxGroup(vector<CheckBox> &items, int left, int top, int padding=DEFAULT_PADDING);
        void Append(CheckBox checkbox);
        void remove(ID id);
        vector<CheckBox> GetItems() const;
        vector<CheckBox> GetCheckedItems() const;
        CheckBox operator[](int idx) const;
        void EventHandle(SDL_Event& event);
        void Update() override ;
    private:
        vector<CheckBox> items;
    };

    class CheckBox : public GroupButton{
    public:
        enum State{
            CHECKED,
            UNCHECKED
        };
        friend class CheckBoxGroup;
        CheckBox();
        explicit CheckBox(string text);
        explicit CheckBox(bool checked);
        CheckBox(string text, bool checked);
        void Check();
        void Uncheck();
        bool IsChecked() const;
        void SetRightColor(SDL_Color color);
        void SetBoxColor(SDL_Color color);
        SDL_Color GetRightColor() const;
        SDL_Color GetBoxColor() const;
        CheckBoxGroup *GetGroup() const;
        void EventHandle(SDL_Event& event) override;
        bool QueryState(unsigned int s) const override;
    protected:
        static const int default_len;
        CheckBoxGroup *group;
        bool checked;
        SDL_Color boxcolor;
        SDL_Color rightcolor;

        void draw() override;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP
