//
// Created by 桂明谦 on 2020/2/8.
//

#include "engin/action/skew.hpp"

vector<Skew> Skew::instances;

Skew* Skew::create(vector<Action*> actions){
    instances.push_back(move(Skew(actions)));
    return &instances[instances.size()-1];
}

Skew* Skew::create(initializer_list<Action*> actionlist){
    instances.push_back(move(Skew(actionlist)));
    return &instances[instances.size()-1];
}

Skew::Skew(vector<Action*> actions){
    this->actions = actions;
}

Skew::Skew(initializer_list<Action*> actionlist){
    for(auto it=actionlist.begin();it!=actionlist.end();it++)
        actions.push_back(*it);
}

void Skew::Play(){
    Action::Play();
    for(Action* action : actions)
        action->Play();
}

void Skew::Pause(){
    Action::Pause();
    for(Action* action : actions)
        action->Pause();
}

void Skew::Stop(){
    Action::Stop();
    for(Action* action : actions)
        action->Stop();

}

void Skew::Step(Sprite* sprite){
    if(isplaying){
        if(actionAllStopped())
            Stop();
        else
            for(Action* action: actions)
                action->Step(sprite);
    }
}

bool Skew::actionAllStopped(){
    bool ret = false;
    for(Action* action: actions)
        ret |= action->IsPlaying();
    return !ret;
}
