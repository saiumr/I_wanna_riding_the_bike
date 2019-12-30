//
// Created by 桂明谦 on 2019/11/30.
//

#ifndef __ANIMATION_HPP__
#define  __ANIMATION_HPP__
#include "SDL.h"
#include "imageEntrepot.hpp"
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

class Animation {
public:
    Animation();
    explicit Animation(vector<Frame> frames);
    explicit Animation(vector<SDL_Texture*> texture, vector<unsigned int> intervals);
    explicit Animation(vector<string> names, vector<unsigned int> intervals);
    void Play();
    void Pause();
    void Stop();
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
    vector<Frame> GetAnimation();
    Frame GetCurrentFrame();
    void SetAnimation(vector<Frame> nframes);
private:
    int count;
    bool isloop;
    unsigned int currentframe;
    bool isplay;
    vector<Frame> animations;
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
