//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/moveby.hpp"

vector<MoveBy> MoveBy::instances;

MoveBy* MoveBy::create(int time, int deltax, int deltay){
    instances.push_back(MoveBy(time, deltax, deltay));
    return &instances[instances.size()-1];
}

MoveBy::MoveBy(int time, int deltax, int deltay):distance({deltax, deltay}){
    this->time = time;
}

void MoveBy::Step(Sprite* sprite){
    if(isplaying){
        if(current_time<time){
            sprite->Translate(static_cast<float>(distance.x)/time, static_cast<float>(distance.y)/time);
            current_time++;
        } else
            Stop();
    }
}
