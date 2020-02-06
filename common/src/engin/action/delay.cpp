//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/delay.hpp"

vector<Delay> Delay::instances;

Delay* Delay::create(int time){
    instances.push_back(move(Delay(time)));
    return &instances[instances.size()-1];
}

Delay::Delay(int time){
    this->time = time;
}

void Delay::Step(Sprite* sprite){
    if(isplaying){
        if(current_time<=time)
            current_time++;
        else
            Stop();
    }
}
