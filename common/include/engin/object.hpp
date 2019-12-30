//
// Created by 桂明谦 on 2019/12/19.
//

#ifndef FARTRACE_OBJECT_HPP
#define FARTRACE_OBJECT_HPP

#include "mmath.hpp"
#include "spdlog/spdlog.h"

class Object {
public:
    Object();
    Object(int x, int y, int w, int h);
    /**
     * @brief 这个函数会返回锚点处坐标，而不是左上角坐标
     * @return 返回锚点处坐标
     */
    Point GetPosition();
    SDL_Size GetSize();
    void Move(int x, int y);
    void Resize(int w, int h);
    void Translate(int delta_x, int delta_y);
    void Scale(float scale_x, float scale_y);
    float GetDegree();
    Pointf GetAnchor();
    void SetAnchorByPercent(float x, float y);
    void SetAnchorByPixel(int x, int y);
    void RotateTo(float degree);
    void RotateDelta(float delta_degree);
protected:
    Rect rect;
    Pointf anchor;
    float angle;

    void SetAnchorByPixel(float x, float y);
};


#endif //FARTRACE_OBJECT_HPP
