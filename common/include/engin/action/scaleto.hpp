//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_SCALETO_HPP
#define I_WANNA_RIDING_THE_BIKE_SCALETO_HPP

#include "action.hpp"

class ScaleTo : public Action{
public:
    static ScaleTo* create(int time, float deltax, float deltay);
    ScaleTo(int time, float deltax, float deltay);
    void Step(Sprite* sprite) override;
private:
    static vector<ScaleTo> instances;
    SDL_Pointf dstscale;
    SDL_Size initsize;
};


#endif //I_WANNA_RIDING_THE_BIKE_SCALETO_HPP
