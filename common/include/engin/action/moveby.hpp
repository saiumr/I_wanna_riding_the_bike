//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_MOVEBY_HPP
#define I_WANNA_RIDING_THE_BIKE_MOVEBY_HPP

#include "engin/action/action.hpp"

class MoveBy:public Action {
public:
    static MoveBy* create(int time, int deltax, int deltay);
    MoveBy(int time, int deltax, int deltay);
    void Step(Sprite* sprite) override;
private:
    static vector<MoveBy> instances;
    SDL_Point distance;
};


#endif //I_WANNA_RIDING_THE_BIKE_MOVEBY_HPP
