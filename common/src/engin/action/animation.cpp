//
// Created by 桂明谦 on 2019/11/30.
//

#include "engin/action/animation.hpp"
#include <utility>

const Frame Frame::EMPTY_FRAME(nullptr, 0);

Frame::Frame(SDL_Texture* texture, int ninterval):image(texture),interval(ninterval){}

Frame::Frame(string name, int ninterval):image(ImageEntrepot::GetImage(std::move(name))),interval(ninterval){}

Frame::Frame():image(nullptr),interval(0){}

void Frame::SetInterval(int interval){
    if(interval<0)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "interval can't less than 0");
    else
        this->interval = interval;
}

void Frame::SetImage(SDL_Texture* image){
    if(image == nullptr)
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Frame's image can't be empty");
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

vector<Animation> Animation::animations;

Animation::Animation():count(0), isloop(false), currentframe(0){
    frames.clear();
}

Animation::Animation(string name, vector<Frame> frames): count(0), frames(std::move(frames)), isloop(false), currentframe(0){
    this->name = name;
}

Animation::Animation(string name, vector<SDL_Texture*> texture, vector<unsigned int> intervals): count(0), isloop(false), currentframe(0){
    this->name = name;
    for(int i=0;i<texture.size();i++){
        Frame frame(texture[i], intervals[i]);
        frames.push_back(frame);
    }
}

Animation* Animation::create(string name, vector<Frame> frames){
    animations.push_back(std::move(Animation(name, frames)));
    return &animations[animations.size()-1];
}

Animation* Animation::create(string name, vector<SDL_Texture*> texture, vector<unsigned int> intervals){
    animations.push_back(std::move(Animation(name, texture, intervals)));
    return &animations[animations.size()-1];
}

Animation* Animation::create(string name, vector<string> names, vector<unsigned int> intervals){
    animations.push_back(std::move(Animation(name, names, intervals)));
    return &animations[animations.size()-1];
}

Animation* Animation::create(vector<Frame> frames){
    animations.push_back(std::move(Animation("", frames)));
    return &animations[animations.size()-1];
}

Animation* Animation::create(vector<SDL_Texture*> texture, vector<unsigned int> intervals){
    animations.push_back(std::move(Animation("", texture, intervals)));
    return &animations[animations.size()-1];
}

Animation* Animation::create(vector<string> names, vector<unsigned int> intervals){
    animations.push_back(std::move(Animation("", names, intervals)));
    return &animations[animations.size()-1];
}

Animation::Animation(string name, vector<string> names, vector<unsigned int> intervals):Animation(){
    this->name = name;
    for(int i=0;i<names.size();i++){
        Frame frame(names[i], intervals[i]);
        frames.push_back(frame);
    }
}

void Animation::EnableLoop(bool willoop){
    isloop = willoop;
}

bool Animation::IsLoop(){
    return isloop;
}

bool Animation::IsPlaying(){
    return isplaying;
}

bool Animation::IsEmpty(){
    return frames.empty();
}

void Animation::Play(){
    isplaying = true;
}

void Animation::Pause(){
    isplaying = false;
}

void Animation::Stop(){
    isplaying = false;
    currentframe = 0;
    count = 0;
}

SDL_Texture* Animation::Step(){
    Frame frame = GetCurrentFrame();
    if(!isplaying)
        return frame.GetImage();
    if(count<frame.GetInterval())
        count++;
    else{
        count = 0;
        if(currentframe == frames.size() - 1){
            if(isloop){
                currentframe = 0;
            }else{
                isplaying = false;
            }
        }else{
            currentframe++;
        }
    }
    return GetCurrentFrame().GetImage();
}

void Animation::Step(Sprite* sprite){
    sprite->SetImage(Step());
}

void Animation::BackAFrame(){
    if(currentframe!=0)
        currentframe--;
    count = 0;
}

void Animation::FrowardAFrame(){
    if(currentframe < frames.size())
        currentframe++;
    count = 0;
}

Frame Animation::GetPrevFrame(){
    return currentframe>0 ? frames[currentframe - 1] : Frame::EMPTY_FRAME;
}

Frame Animation::GetNextFrame(){
    return currentframe < frames.size() ? frames[currentframe + 1] : Frame::EMPTY_FRAME;
}

unsigned int Animation::GetCurrentFrameNum(){
    return currentframe+1;
}

void Animation::StepNext(){
    if(currentframe < frames.size() - 1) {
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
    return frames;
}

Frame Animation::GetCurrentFrame(){
    return frames[currentframe];
}

void Animation::SetAnimation(vector<Frame> nframes){
    frames = std::move(nframes);
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