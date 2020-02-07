//
// Created by 桂明谦 on 2020/2/8.
//

#ifndef I_WANNA_RIDING_THE_BIKE_LOOPACTION_HPP
#define I_WANNA_RIDING_THE_BIKE_LOOPACTION_HPP

#include "action.hpp"

class LoopAction : public Action{
public:
    enum{
        ENDLESS=0
    };
    static LoopAction* create(Action* action, int times);
    LoopAction(Action* action, int times);
    void Play() override;
    void Pause() override;
    void Stop() override;
    void Step(Sprite* sprite) override;
private:
    static vector<LoopAction> instances;
    Action* action;
};


#endif //I_WANNA_RIDING_THE_BIKE_LOOPACTION_HPP
