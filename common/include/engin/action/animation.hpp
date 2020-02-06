//
// Created by 桂明谦 on 2019/11/30.
//

#ifndef __ANIMATION_HPP__
#define  __ANIMATION_HPP__
#include "SDL.h"
#include "engin/imageEntrepot.hpp"
#include "engin/action/action.hpp"
#include <vector>
#include <string>
using namespace std;

class Frame{
public:
    static const Frame EMPTY_FRAME;
    Frame(SDL_Texture* texture, int ninterval);
    Frame(string name, int ninterval);
    Frame();
    void SetInterval(int interval);
    void SetImage(SDL_Texture* image);
    void SetImage(string name);
    bool IsValid();
    SDL_Texture* GetImage();
    unsigned int GetInterval();
private:
    unsigned int interval;
    SDL_Texture* image;
};

class Animation:public Action {
public:
    static Animation* create(string name, vector<Frame> frames);
    static Animation* create(string name, vector<SDL_Texture*> texture, vector<unsigned int> intervals);
    static Animation* create(string name, vector<string> names, vector<unsigned int> intervals);
    static Animation* create(vector<Frame> frames);
    static Animation* create(vector<SDL_Texture*> texture, vector<unsigned int> intervals);
    static Animation* create(vector<string> names, vector<unsigned int> intervals);
    Animation();
    Animation(string name, vector<Frame> frames);
    Animation(string name, vector<SDL_Texture*> texture, vector<unsigned int> intervals);
    Animation(string name, vector<string> names, vector<unsigned int> intervals);
    void Play() override;
    void Pause() override;
    void Stop() override;
    void BackAFrame();
    void FrowardAFrame();
    bool IsEmpty();
    bool IsPlaying();
    void EnableLoop(bool willoop);
    bool IsLoop();
    Frame GetPrevFrame();
    Frame GetNextFrame();
    void StepNext();
    void StepPrev();
    unsigned int GetCurrentFrameNum();
    SDL_Texture* Step();
    void Step(Sprite* sprite) override;
    vector<Frame> GetAnimation();
    Frame GetCurrentFrame();
    void SetAnimation(vector<Frame> nframes);
private:
    static vector<Animation> animations;
    int count;
    bool isloop;
    unsigned int currentframe;
    vector<Frame> frames;
};

class Animatable{
public:
    SDL_Texture* GetCurrentImage();
    Animation GetAnimation();
    void SetAnimation(Animation ani);
    void SetAnimation(vector<Frame> frames);
    void SetAnimation(vector<string> names, vector<int> intervals);
    void PlayAnimation();
    void PauseAnimation();
    void StopAnimation();
    void EnableLoop(bool loop);
    bool IsPlay();
    bool IsLoop();
protected:
    Animation animation;
};

#endif
