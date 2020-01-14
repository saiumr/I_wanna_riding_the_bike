//
// Created by 桂明谦 on 2020/1/14.
//

#ifndef I_WANNA_RIDING_THE_BIKE_GROUPBUTTON_HPP
#define I_WANNA_RIDING_THE_BIKE_GROUPBUTTON_HPP

#include "button.hpp"
#include <vector>
using namespace std;

namespace GUI {

    using ID = unsigned int;
    const ID ERROR_ID = 0;

    class GroupButton;

    class GroupButtonGroup{
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

        GroupButtonGroup();
        GroupButtonGroup(int left, int top, int padding=DEFAULT_PADDING);
        int GetPadding();
        void SetPadding(int padding);
        void SetItemAlignType(ItemAlignType type);
        void SetTextWarpType(TextWarpType type);
        ItemAlignType GetItemAlignType();
        TextWarpType GetTextWarpType();
        void SetTopLeft(int x, int y);
        SDL_Point GetTopLeft() const;
        /**
         * 这个函数用来计算字体和按钮的位置
         * @warning 按钮和按钮之间的间隔只隔一个padding，而不会按照字体大小适配
         * @param idx 目前要计算的按钮和字体序号
         * @param button_pos 按钮坐标，作为返回值的参数
         * @param button_size 按钮大小
         * @param font_pos 字体坐标，作为返回值的参数
         */
        void CalculatePosition(int idx, SDL_Point& button_pos, SDL_Size button_size, SDL_Point& font_pos, SDL_Size font_size);
        virtual void Update() = 0;
    protected:
        ItemAlignType itemAlignType;
        TextWarpType textWarpType;
        ID current_free_item_id;
        SDL_Point tl;
        int padding;
        static const int DEFAULT_PADDING;
    };

    class GroupButton: protected Button {
    public:
        friend class GroupButtonGroup;
        GroupButton();
        GroupButton(ID nid);
        ID GetID() const;

    protected:
        ID id;
    };

}

#endif //I_WANNA_RIDING_THE_BIKE_GROUPBUTTON_HPP
