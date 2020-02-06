//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_DELAY_HPP
#define I_WANNA_RIDING_THE_BIKE_DELAY_HPP

#include "action.hpp"

class Delay : public Action{
public:
    static Delay* create(int time);
    Delay(int time);
    void Play() override;
    void Stop() override;
    void Pause() override;
    void Step(Sprite* sprite) override;
private:
    static vector<Delay> instances;
};


#endif //I_WANNA_RIDING_THE_BIKE_DELAY_HPP
