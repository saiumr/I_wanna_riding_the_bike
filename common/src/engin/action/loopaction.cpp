//
// Created by 桂明谦 on 2020/2/8.
//

#include "engin/action/loopaction.hpp"

vector<LoopAction> LoopAction::instances;

LoopAction* LoopAction::create(Action* action, int times){
    instances.push_back(move(LoopAction(action, times)));
    return &instances[instances.size()-1];
}

LoopAction::LoopAction(Action* action, int times){
    this->action = action;
    this->time = times;
}

void LoopAction::Play(){
    Action::Play();
    if(action!=nullptr)
        action->Play();
}

void LoopAction::Pause(){
    Action::Pause();
    if(action!=nullptr)
        action->Pause();
}

void LoopAction::Stop(){
    Action::Stop();
    if(action!=nullptr)
        action->Stop();
}

void LoopAction::Step(Sprite* sprite){
    if(isplaying){
        if(time==ENDLESS) {
            if (!action->IsPlaying())
                action->Play();
        }else{
            if(!action->IsPlaying() && current_time<time){
                action->Play();
                current_time++;
            }
            if(current_time>=time)
                Stop();
        }
        action->Step(sprite);
    }
}
