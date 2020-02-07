//
// Created by 桂明谦 on 2020/2/7.
//

#include "engin/action/sequence.hpp"

vector<Sequence> Sequence::instances;

Sequence* Sequence::create(vector<Action*> actions){
    instances.push_back(move(Sequence(actions)));
    return &instances[instances.size()-1];
}

Sequence* Sequence::create(initializer_list<Action*> initializerList){
    instances.push_back(move(Sequence(initializerList)));
    return &instances[instances.size()-1];
}

Sequence::Sequence(vector<Action*> actions):current_action_idx(0){
    this->actions = actions;
}

Sequence::Sequence(initializer_list<Action*> actionlist):current_action_idx(0){
    for(auto it=actionlist.begin();it!=actionlist.end();it++)
        actions.push_back(*it);
}

void Sequence::Play(){
    Action::Play();
    actions[current_action_idx]->Play();
}

void Sequence::Pause(){
    Action::Pause();
    actions[current_action_idx]->Pause();
}

void Sequence::Stop(){
    Action::Stop();
    current_action_idx = 0;
    actions[current_action_idx]->Stop();
}

void Sequence::Step(Sprite* sprite){
    if(isplaying){
        if(!actions[current_action_idx]->IsPlaying()) {
            current_action_idx++;
            if(current_action_idx>=actions.size())
                Stop();
            else
                actions[current_action_idx]->Play();
        }
        actions[current_action_idx]->Step(sprite);
    }
}
