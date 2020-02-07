//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/scaleto.hpp"

vector<ScaleTo> ScaleTo::instances;

ScaleTo* ScaleTo::create(int time, float deltax, float deltay){
    instances.push_back(move(ScaleTo(time, deltax, deltay)));
    return &instances[instances.size()-1];
}

ScaleTo::ScaleTo(int time, float deltax, float deltay):initsize({-1, -1}),dstscale({deltax, deltay}){
    this->time = time;
}

void ScaleTo::Step(Sprite* sprite){
    if(initsize.w==-1 && initsize.h==-1)
        initsize = sprite->GetSize();
    if(isplaying){
        if(current_time<time){
            float factorx, factory;
            float prop = current_time/ static_cast<float>(time);
            if(dstscale.x<=1){
                factorx = 1-((1-dstscale.x)*prop);
            } else{
                factorx = (dstscale.x-1)*prop+1;
            }
            if(dstscale.y<=1){
                factory = 1-((1-dstscale.y)*prop);
            } else{
                factory = (dstscale.y-1)*prop+1;
            }
            sprite->Resize(initsize.w*factorx, initsize.h*factory);
            current_time++;
        } else
            Stop();
    }
}
