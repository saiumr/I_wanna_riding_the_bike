//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/rotateby.hpp"

vector<RotateBy> RotateBy::instances;

RotateBy* RotateBy::create(int time, float angle){
    instances.push_back(std::move(RotateBy(time, angle)));
    return &instances[instances.size()-1];
}

RotateBy::RotateBy(int time, float angle):deltaangle(angle){
    this->time = time;
}

void RotateBy::Step(Sprite* sprite){
    if(isplaying){
        if(current_time<=time){
            sprite->RotateDelta(deltaangle/time);
            current_time++;
        }else{
            Stop();
        }
    }
}
