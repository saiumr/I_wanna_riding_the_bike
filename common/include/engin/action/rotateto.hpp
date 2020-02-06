//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_ROTATETO_HPP
#define I_WANNA_RIDING_THE_BIKE_ROTATETO_HPP

#include "action.hpp"

class RotateTo : public Action{
public:
    static RotateTo* create(int time, float angle);
    RotateTo(int time, int angle);
    void Step(Sprite* sprite) override;
private:
    static vector<RotateTo> instances;
    float dstangle;
    float distance;
};

#endif //I_WANNA_RIDING_THE_BIKE_ROTATETO_HPP
