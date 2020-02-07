//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/rotateto.hpp"

vector<RotateTo> RotateTo::instances;

RotateTo* RotateTo::create(int time, float angle){
    instances.push_back(move(RotateTo(time, angle)));
    return &instances[instances.size()-1];
}

RotateTo::RotateTo(int time, int angle):dstangle(angle){
    this->time = time;
    distance = 0;
}

void RotateTo::Step(Sprite* sprite){
    if(distance==0) {
        distance = dstangle - sprite->GetDegree();
    }
    if(isplaying){
        if(current_time<time){
            sprite->RotateDelta(distance/time);
            current_time++;
        } else
            Stop();
    }
}
