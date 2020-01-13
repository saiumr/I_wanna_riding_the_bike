//
// Created by 桂明谦 on 2020/1/10.
//

#ifndef I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP
#define I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP

#include "button.hpp"
#include <vector>
using namespace std;

namespace GUI {

    using ID = unsigned int;
    const ID ERROR_ID = 0;

    class CheckBox;

    class CheckBoxGroup {
    public:
        enum class TextWarpType{
            TOP,
            BUTTOM,
            LEFT,
            RIGHT
        };
       enum class ItemAlignType{
            VERTICAL,
            HORIZONTAL
        };

        CheckBoxGroup();
        CheckBoxGroup(vector<CheckBox> &items, int left, int top, int padding=DEFAULT_PADDING);
        int GetPadding();
        void SetPadding(int padding);
        void SetItemAlignType(ItemAlignType type);
        void SetTextWarpType(TextWarpType type);
        ItemAlignType GetItemAlignType();
        TextWarpType GetTextWarpType();
        void Append(CheckBox checkbox);
        void remove(ID id);
        vector<CheckBox> GetItems() const;
        vector<CheckBox> GetCheckedItems() const;
        CheckBox operator[](int idx) const;
        void EventHandle(SDL_Event& event);
        ID GetID() const;
        void SetTopLeft(int x, int y);
        SDL_Point GetTopLeft() const;
        void Update();
    private:
        ID id;
        ItemAlignType itemAlignType;
        TextWarpType textWarpType;
        ID current_free_item_id;
        vector<CheckBox> items;
        static ID current_free_group_id;
        SDL_Point tl;
        int padding;
        static const int DEFAULT_PADDING;
    };

    class CheckBox : protected Button {
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
        ID GetID();
        SDL_Color GetRightColor() const;
        SDL_Color GetBoxColor() const;
        CheckBoxGroup *GetGroup() const;
        void EventHandle(SDL_Event& event) override;
        bool QueryState(unsigned int s) override;
    private:
        static const int default_len;

        CheckBoxGroup *group;
        bool checked;
        ID id;
        SDL_Color boxcolor;
        SDL_Color rightcolor;

        void draw() override;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_CHECKBOX_HPP
