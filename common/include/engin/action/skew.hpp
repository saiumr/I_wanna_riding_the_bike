//
// Created by 桂明谦 on 2020/2/8.
//

#ifndef I_WANNA_RIDING_THE_BIKE_SKEW_HPP
#define I_WANNA_RIDING_THE_BIKE_SKEW_HPP

#include "sequence.hpp"

class Skew : public Action{
public:
    static Skew* create(vector<Action*> actions);
    static Skew* create(initializer_list<Action*> actionlist);
    Skew(vector<Action*> actions);
    Skew(initializer_list<Action*> actions);
    void Step(Sprite* sprite) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
private:
    static vector<Skew> instances;
    vector<Action*> actions;
    bool actionAllStopped();
};


#endif //I_WANNA_RIDING_THE_BIKE_SKEW_HPP
