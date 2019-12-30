//
// Created by 桂明谦 on 2019/11/30.
//

#include "engin/animation.hpp"
#include <utility>

const Frame Frame::EMPTY_FRAME(nullptr, 0);

Frame::Frame(SDL_Texture* texture, int ninterval):image(texture),interval(ninterval){}

Frame::Frame(string name, int ninterval):image(ImageEntrepot::GetImage(std::move(name))),interval(ninterval){}

Frame::Frame():image(nullptr),interval(0){}

void Frame::SetInterval(int interval){
    if(interval<0)
        cerr << __FUNCTION__ << ":interval can't less than 0" << endl;
    else
        this->interval = interval;
}

void Frame::SetImage(SDL_Texture* image){
    if(image == nullptr)
        cerr<<__FUNCTION__<<":Frame's image can't be empty"<<endl;
    else
        this->image = image;
}

void Frame::SetImage(string name){
    image = ImageEntrepot::GetImage(std::move(name));
}

SDL_Texture* Frame::GetImage(){
    return image;
}

unsigned int Frame::GetInterval(){
    return interval;
}

bool Frame::IsValid(){
    return image==nullptr||interval==0;
}

Animation::Animation(): isplay(false), count(0), isloop(false), currentframe(0){
   animations.clear();
}

Animation::Animation(vector<Frame> frames): isplay(false), count(0), animations(std::move(frames)), isloop(false), currentframe(0){
}

Animation::Animation(vector<SDL_Texture*> texture, vector<unsigned int> intervals): count(0), isplay(false), isloop(false), currentframe(0){
    for(int i=0;i<texture.size();i++){
        Frame frame(texture[i], intervals[i]);
        animations.push_back(frame);
    }
}

void Animation::EnableLoop(bool willoop){
    isloop = willoop;
}

bool Animation::IsLoop(){
    return isloop;
}

bool Animation::IsPlaying(){
    return isplay;
}

bool Animation::IsEmpty(){
    return animations.empty();
}

Animation::Animation(vector<string> names, vector<unsigned int> intervals):Animation(){
    for(int i=0;i<names.size();i++){
        Frame frame(names[i], intervals[i]);
        animations.push_back(frame);
    }
}

void Animation::Play(){
    isplay = true;
}

void Animation::Pause(){
    isplay = false;
}

void Animation::Stop(){
    isplay = false;
    currentframe = 0;
    count = 0;
}

SDL_Texture* Animation::Step(){
    Frame frame = GetCurrentFrame();
    if(!isplay)
        return frame.GetImage();
    if(count<frame.GetInterval())
        count++;
    else{
        count = 0;
        if(currentframe==animations.size()-1){
            if(isloop){
                currentframe = 0;
            }else{
                isplay = false;
            }
        }else{
            currentframe++;
        }
    }
    return GetCurrentFrame().GetImage();
}

void Animation::BackAFrame(){
    if(currentframe!=0)
        currentframe--;
    count = 0;
}

void Animation::FrowardAFrame(){
    if(currentframe<animations.size())
        currentframe++;
    count = 0;
}

Frame Animation::GetPrevFrame(){
    return currentframe>0?animations[currentframe-1]:Frame::EMPTY_FRAME;
}

Frame Animation::GetNextFrame(){
    return currentframe<animations.size()?animations[currentframe+1]:Frame::EMPTY_FRAME;
}

unsigned int Animation::GetCurrentFrameNum(){
    return currentframe+1;
}

void Animation::StepNext(){
    if(currentframe<animations.size()-1) {
        currentframe++;
        count = 0;
    }
}

void Animation::StepPrev(){
    if(currentframe>0){
        currentframe--;
        count = 0;
    }
}

vector<Frame> Animation::GetAnimation(){
    return animations;
}

Frame Animation::GetCurrentFrame(){
    return animations[currentframe];
}

void Animation::SetAnimation(vector<Frame> nframes){
    animations = std::move(nframes);
}

SDL_Texture* Animatable::GetCurrentImage(){
    return animation.GetCurrentFrame().GetImage();
}

void Animatable::SetAnimation(vector<Frame> frames){
    animation.SetAnimation(std::move(frames));
}

void Animatable::SetAnimation(vector<string> names, vector<int> intervals){
    vector<Frame> frames;
    for(int i=0;i<names.size();i++){
        Frame frame(names[i], intervals[i]);
        frames.push_back(frame);
    }
    SetAnimation(frames);
}

Animation Animatable::GetAnimation(){
    return animation;
}

void Animatable::SetAnimation(Animation ani){
    animation = std::move(ani);
}

void Animatable::PlayAnimation(){
    animation.Play();
}

void Animatable::PauseAnimation(){
    animation.Pause();
}

void Animatable::StopAnimation(){
    animation.Stop();
}

void Animatable::EnableLoop(bool loop){
    animation.EnableLoop(loop);
}

bool Animatable::IsPlay(){
    return animation.IsPlaying();
}

bool Animatable::IsLoop(){
    return animation.IsLoop();
}