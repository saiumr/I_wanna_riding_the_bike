//
// Created by 桂明谦 on 2020/2/7.
//

#ifndef I_WANNA_RIDING_THE_BIKE_SEQUENCE_HPP
#define I_WANNA_RIDING_THE_BIKE_SEQUENCE_HPP

#include "action.hpp"

class Sequence : public Action{
public:
    static Sequence* create(vector<Action*> actions);
    static Sequence* create(initializer_list<Action*> actionlist);
    Sequence(vector<Action*> actions);
    Sequence(initializer_list<Action*> initializerList);
    void Play() override;
    void Pause() override;
    void Stop() override;
    void Step(Sprite* sprite) override;
private:
    static vector<Sequence> instances;
    vector<Action*> actions;
    int current_action_idx;
};


#endif //I_WANNA_RIDING_THE_BIKE_SEQUENCE_HPP
