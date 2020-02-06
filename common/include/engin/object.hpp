//
// Created by 桂明谦 on 2019/12/19.
//

#ifndef FARTRACE_OBJECT_HPP
#define FARTRACE_OBJECT_HPP

#include "mmath.hpp"
#include <iostream>
using namespace std;

class Object {
public:
    Object();
    Object(float x, float y, int w, int h);
    /**
     * @brief 这个函数会返回锚点处坐标，而不是左上角坐标
     * @return 返回锚点处坐标
     */
    Pointf GetPosition();
    Point GetIntPosition();
    SDL_Size GetSize();
    void Move(float x, float y);
    void Resize(int w, int h);
    void Translate(float delta_x, float delta_y);
    void Scale(float scale_x, float scale_y);
    float GetDegree();
    Pointf GetAnchor();
    void SetAnchorByPercent(float x, float y);
    void SetAnchorByPixel(int x, int y);
    void RotateTo(float degree);
    void RotateDelta(float delta_degree);
protected:
    Rectf rect;
    Pointf anchor;
    float angle;
};


#endif //FARTRACE_OBJECT_HPP
