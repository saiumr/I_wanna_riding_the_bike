//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_ROTATEBY_HPP
#define I_WANNA_RIDING_THE_BIKE_ROTATEBY_HPP

#include "action.hpp"

class RotateBy : public Action {
public:
    static RotateBy* create(int time, float angle);
    RotateBy(int time, float angle);
    void Step(Sprite* sprite) override;
private:
    static vector<RotateBy> instances;
    float deltaangle;
};


#endif //I_WANNA_RIDING_THE_BIKE_ROTATEBY_HPP
