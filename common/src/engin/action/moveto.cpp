//
// Created by 桂明谦 on 2020/2/6.
//

#include "engin/action/moveto.hpp"

vector<MoveTo> MoveTo::instances;

MoveTo* MoveTo::create(int time, int x, int y){
    instances.push_back(MoveTo(time, x, y));
    return &instances[instances.size()-1];
}

MoveTo::MoveTo(int time, int x, int y):dstpos({x, y}),distance({0, 0}){
    this->time = time;
}

void MoveTo::Step(Sprite* sprite){
    if(distance.x==0 && distance.y==0) {
        SDL_Pointf sprite_pos = sprite->GetPosition();
        distance.x = dstpos.x-sprite_pos.x;
        distance.y = dstpos.y-sprite_pos.y;
    }
    if(isplaying){
        if(current_time<time){
            sprite->Translate(static_cast<float>(distance.x)/time, static_cast<float>(distance.y)/time);
            current_time++;
        } else
            Stop();
    }
}
