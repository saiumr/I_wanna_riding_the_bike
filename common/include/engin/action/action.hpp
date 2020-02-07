//
// Created by 桂明谦 on 2020/2/6.
//

#ifndef I_WANNA_RIDING_THE_BIKE_ACTION_HPP
#define I_WANNA_RIDING_THE_BIKE_ACTION_HPP

#include "engin/sprite.hpp"

class Sprite;

class Action {
public:
    Action();
    virtual void Step(Sprite* sprite) = 0;
    virtual void Play();
    virtual void Stop();
    virtual void Pause();
    bool IsPlaying();
    //现在下面两个函数还没什么用，还没有针对动作编写名称
    string GetName();
    void SetName(string name);
protected:
    bool isplaying;
    int time;
    int current_time;
    string name;
};


#endif //I_WANNA_RIDING_THE_BIKE_ACTION_HPP